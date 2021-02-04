/**
 * @file Dragon_CANbus.c
 * @copyright TU Brno Racing
 * @author Tomas Lorenc
 * @date 2019-2020
 * @brief Source file for dragon CAN communication.
 * @ver 2.1
 * File contain core functions.
 */

#include "Dragon_CANbus.h"

#define TX_CAN1_BUFFER_SIZE 8 // max 255
#ifdef _DUAL_CAN_ACTIVATE
#    define TX_CAN2_BUFFER_SIZE 8 // max 255
#endif                            //_DUAL_CAN_ACTIVATE

#define TXBUFF_YES (0x00000000U) /*!< All msg will been send   */
#define TXBUFF_NO (0x00000008U)  /*!< Only new msg will been send */

typedef struct
{
    uint16_t msgID;
    size_t msgSize;
    uint16_t msgConf;
    uint8_t aData[8];
} buffCanTypedef;

#ifdef __EXTENDED_CAN_ACTIVATE
uint8_t ExtendEnable = 0;
#endif

static uint8_t TXCAN1buffHead = 0; // new data
static uint8_t TXCAN1buffTill = 0; // no reading data
static buffCanTypedef TXCAN1buff[TX_CAN1_BUFFER_SIZE];

#ifdef _DUAL_CAN_ACTIVATE
static uint8_t TXCAN2buffHead = 0; // new data
static uint8_t TXCAN2buffTill = 0; // no reading data
static buffCanTypedef TXCAN2buff[TX_CAN2_BUFFER_SIZE];
#endif //_DUAL_CAN_ACTIVATE

static CAN_HandleTypeDef* defineCAN1 = NULL; // CAN1 handler
#ifdef _DUAL_CAN_ACTIVATE
static CAN_HandleTypeDef* defineCAN2 = NULL; // CAN2 handler
#endif //_DUAL_CAN_ACTIVATE

#ifdef _DUAL_CAN_ACTIVATE
HAL_StatusTypeDef CANbus_Init(CAN_HandleTypeDef* hcan1, CAN_HandleTypeDef* hcan2)
{
#else
HAL_StatusTypeDef CANbus_Init(CAN_HandleTypeDef* hcan1)
{
#endif //_DUAL_CAN_ACTIVATE

    /*--CAN1 init--*/
    defineCAN1 = hcan1; // copy pointer to main CAN1 Handler

    if (HAL_CAN_ActivateNotification(defineCAN1, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
    {
        // Activate interrupt CAN_IT_TX_MAILBOX_EMPTY
        return HAL_ERROR;
    }

#ifdef _CAN1def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_ActivateNotification(defineCAN1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        // Activate interrupt CAN_IT_RX_FIFO0_MSG_PENDING
#else
    if (HAL_CAN_ActivateNotification(defineCAN1, CAN_IT_RX_FIFO0_FULL) != HAL_OK)
    {
        // Activate interrupt CAN_IT_RX_FIFO0_FULL
#endif //_CAN1def_ONLY_INTERRUPT_MODE
        return HAL_ERROR;
    }

    if (HAL_CAN_ActivateNotification(defineCAN1, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
    {
        // Activate interrupt CAN_IT_RX_FIFO0_FULL
        return HAL_ERROR;
    }

#ifdef _DUAL_CAN_ACTIVATE /*--CAN2 init--*/

    defineCAN2 = hcan2; // copy pointer to main CAN2 Handler

    if (HAL_CAN_ActivateNotification(defineCAN2, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
    {
        // Activate interrupt CAN_IT_TX_MAILBOX_EMPTY
        return HAL_ERROR;
    }

#    ifdef _CAN2def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_ActivateNotification(defineCAN2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        // Activate interrupt CAN_IT_RX_FIFO0_MSG_PENDING
#    else
    if (HAL_CAN_ActivateNotification(defineCAN2, CAN_IT_RX_FIFO0_FULL) != HAL_OK)
    {
        // Activate interrupt CAN_IT_RX_FIFO0_FULL
#    endif
        return HAL_ERROR;
    }

    if (HAL_CAN_ActivateNotification(defineCAN2, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
    {
        // Activate interrupt CAN_IT_RX_FIFO0_FULL
        return HAL_ERROR;
    }
#endif //_DUAL_CAN_ACTIVATE

    return HAL_OK;
}

HAL_StatusTypeDef CANbus_FilterInit()
{
    if (defineCAN1 == NULL)
    { // if defineCAN is not empty
        return HAL_ERROR;
    }

    CAN_FilterTypeDef tmpFilterDef; // temporary variable
    tmpFilterDef.FilterMode           = CAN_FILTERMODE_IDMASK;
    tmpFilterDef.FilterScale          = CAN_FILTERSCALE_16BIT;
    tmpFilterDef.SlaveStartFilterBank = 14; // 14 filters for ONE CANbus!!!

    for (uint8_t i = 0; i < 14; i++)
    {
        if (__CAN1_FILTERLIST[i][5] == 1)
        {                                                                     // if filter is activate
            tmpFilterDef.FilterBank           = i;                            // number of filter bank
            tmpFilterDef.FilterFIFOAssignment = __CAN1_FILTERLIST[i][4];      // FIFO
            tmpFilterDef.FilterActivation     = __CAN1_FILTERLIST[i][5];      // enable
            tmpFilterDef.FilterMaskIdHigh     = __CAN1_FILTERLIST[i][2] << 5; // mask1
            tmpFilterDef.FilterMaskIdLow      = __CAN1_FILTERLIST[i][0] << 5; // mask0
            tmpFilterDef.FilterIdHigh         = __CAN1_FILTERLIST[i][3] << 5; // mask1
            tmpFilterDef.FilterIdLow          = __CAN1_FILTERLIST[i][1] << 5; // ID0

            if (HAL_CAN_ConfigFilter(defineCAN1, &tmpFilterDef) != HAL_OK)
            {
                return HAL_ERROR; // Filter configuration Error
            }
        }
    }

#ifdef _DUAL_CAN_ACTIVATE /*--CAN2 init--*/
    for (uint8_t i = 0; i < 14; i++)
    {
        if (__CAN2_FILTERLIST[i][5] == 1)
        {                                                                     // if filter is activate
            tmpFilterDef.FilterBank           = i;                            // number of filter bank
            tmpFilterDef.FilterFIFOAssignment = __CAN2_FILTERLIST[i][4];      // FIFO
            tmpFilterDef.FilterActivation     = __CAN2_FILTERLIST[i][5];      // enable
            tmpFilterDef.FilterMaskIdHigh     = __CAN2_FILTERLIST[i][2] << 5; // mask1
            tmpFilterDef.FilterMaskIdLow      = __CAN2_FILTERLIST[i][0] << 5; // mask0
            tmpFilterDef.FilterIdHigh         = __CAN2_FILTERLIST[i][3] << 5; // mask1
            tmpFilterDef.FilterIdLow          = __CAN2_FILTERLIST[i][1] << 5; // ID0

            if (HAL_CAN_ConfigFilter(defineCAN2, &tmpFilterDef) != HAL_OK)
            {
                return HAL_ERROR; // Filter configuration Error
            }
        }
    }
#endif //_DUAL_CAN_ACTIVATE
    return HAL_OK;
}

#ifdef __EXTENDED_CAN_ACTIVATE
HAL_StatusTypeDef CANbus_ExtendedFilterInit()
{
    ExtendEnable = 1;
    CAN_FilterTypeDef tmpFilterDef; // temporary variable
    tmpFilterDef.FilterMode           = CAN_FILTERMODE_IDMASK;
    tmpFilterDef.FilterScale          = CAN_FILTERSCALE_32BIT;
    tmpFilterDef.FilterBank           = 0;                 // number of filter bank
    tmpFilterDef.FilterFIFOAssignment = CAN_FILTER_FIFO1;  // FIFO
    tmpFilterDef.FilterActivation     = CAN_FILTER_ENABLE; // enable
    tmpFilterDef.FilterMaskIdHigh     = 0x0;               // mask1
    tmpFilterDef.FilterMaskIdLow      = 0x0;               // mask0
    tmpFilterDef.FilterIdHigh         = 0x0;               // mask1
    tmpFilterDef.FilterIdLow          = 0x0;               // ID0
    if (HAL_CAN_ConfigFilter(defineCAN1, &tmpFilterDef) != HAL_OK)
    {
        return HAL_ERROR; // Filter configuration Error
    }
    return HAL_OK;
}
#endif //__EXTENDED_CAN_ACTIVATE

void CAN1bus_ReadProcessFIFO0()
{
    CAN_RxHeaderTypeDef tmpRxHeader;
    uint8_t RxData[8];

    if (HAL_CAN_GetRxMessage(defineCAN1, CAN_RX_FIFO0, &tmpRxHeader, RxData) != HAL_OK)
    {
        return; // empty FIFO
    }
    do
    {
        if ((tmpRxHeader.IDE == CAN_ID_STD) && (__CAN1_CALLBACKLIST[tmpRxHeader.StdId] != NULL))
        {
            __CAN1_CALLBACKLIST[tmpRxHeader.StdId](RxData); // start callback function
        }
    } while (HAL_CAN_GetRxMessage(defineCAN1, CAN_RX_FIFO0, &tmpRxHeader, RxData) == HAL_OK); // if FIFO have next msg.
}

void CAN1bus_ReadProcessFIFO1()
{
    CAN_RxHeaderTypeDef tmpRxHeader;
    uint8_t RxData[8];

    if (HAL_CAN_GetRxMessage(defineCAN1, CAN_RX_FIFO1, &tmpRxHeader, RxData) != HAL_OK)
    {
        return; // empty FIFO1
    }
    do
    {
#ifdef __EXTENDED_CAN_ACTIVATE
        if (ExtendEnable == 0)
        {
#endif //__EXTENDED_CAN_ACTIVATE
            if ((tmpRxHeader.IDE == CAN_ID_STD) && (__CAN1_CALLBACKLIST[tmpRxHeader.StdId] != NULL))
            {
                __CAN1_CALLBACKLIST[tmpRxHeader.StdId](RxData); // start callback function
            }
#ifdef __EXTENDED_CAN_ACTIVATE
        }
        else if (tmpRxHeader.IDE == CAN_ID_EXT)
        {
            _CANext_func_callback(RxData, tmpRxHeader.ExtId);
        }
        else if (tmpRxHeader.IDE == CAN_ID_STD)
        {
            _CANext_func_callback(RxData, tmpRxHeader.StdId);
        }
#endif //__EXTENDED_CAN_ACTIVATE

    } while (HAL_CAN_GetRxMessage(defineCAN1, CAN_RX_FIFO1, &tmpRxHeader, RxData) == HAL_OK); // if FIFO have next msg.
}

#ifdef _DUAL_CAN_ACTIVATE /*--CAN2 Read--*/

void CAN2bus_ReadProcessFIFO0()
{
    CAN_RxHeaderTypeDef tmpRxHeader;
    uint8_t RxData[8];

    if (HAL_CAN_GetRxMessage(defineCAN2, CAN_RX_FIFO0, &tmpRxHeader, RxData) != HAL_OK)
    {
        return; // empty FIFO
    }
    do
    {
        if ((tmpRxHeader.IDE == CAN_ID_STD) && (__CAN2_CALLBACKLIST[tmpRxHeader.StdId] != NULL))
        {
            __CAN2_CALLBACKLIST[tmpRxHeader.StdId](RxData); // start callback function
        }
    } while (HAL_CAN_GetRxMessage(defineCAN2, CAN_RX_FIFO0, &tmpRxHeader, RxData) == HAL_OK); // if FIFO have next msg.
}

void CAN2bus_ReadProcessFIFO1()
{
    CAN_RxHeaderTypeDef tmpRxHeader;
    uint8_t RxData[8];

    if (HAL_CAN_GetRxMessage(defineCAN2, CAN_RX_FIFO1, &tmpRxHeader, RxData) != HAL_OK)
    {
        return; // empty FIFO1
    }
    do
    {
        if ((tmpRxHeader.IDE == CAN_ID_STD) && (__CAN2_CALLBACKLIST[tmpRxHeader.StdId] != NULL))
        {
            __CAN2_CALLBACKLIST[tmpRxHeader.StdId](RxData); // start callback function
        }

    } while (HAL_CAN_GetRxMessage(defineCAN2, CAN_RX_FIFO1, &tmpRxHeader, RxData) == HAL_OK); // if FIFO have next msg.
}

#endif //_DUAL_CAN_ACTIVATE

HAL_StatusTypeDef CAN1bus_SendData(uint16_t msgID, size_t msgSize, uint16_t msgCnf, uint8_t aData[])
{
    if (HAL_CAN_GetTxMailboxesFreeLevel(defineCAN1) != 0)
    { // Check that all the Tx mailboxes are not full

        CAN_TxHeaderTypeDef tmpTxHeader;
        uint8_t tmpData[8];
        uint32_t mailboxNumber; // number of used mailb - kničemu

        tmpTxHeader.StdId              = msgID;                   // ID
        tmpTxHeader.IDE                = CAN_ID_STD;              // 11 bit ID
        tmpTxHeader.RTR                = msgCnf & CAN_RTR_REMOTE; // send data or request
        tmpTxHeader.DLC                = msgSize;                 // size of message
        tmpTxHeader.TransmitGlobalTime = DISABLE;                 //!!!!
        for (uint8_t i = 0; i < msgSize; ++i)
        {
            tmpData[i] = aData[i];
        } // write msg to mailbox
        if (HAL_CAN_AddTxMessage(defineCAN1, &tmpTxHeader, tmpData, &mailboxNumber) != HAL_OK)
        {
            return HAL_ERROR;
        }
    }
    else
    { // write msg to buffer
        if (((TXCAN1buffHead + 1) % TX_CAN1_BUFFER_SIZE) == TXCAN1buffTill)
        { // if buffer is full
            return HAL_BUSY;
        }
        else
        {

            uint8_t tmpTXbufftill = TXCAN1buffTill;
            while (tmpTXbufftill != TXCAN1buffHead)
            {
                if (TXCAN1buff[tmpTXbufftill].msgID == msgID)
                { // if buff id agree with new id
                    if ((msgCnf & CANdef_ALLMSG) == 0)
                    {                                                   // if selected send only new msg
                        TXCAN1buff[tmpTXbufftill].msgConf |= TXBUFF_NO; // deactivate msg
                    }
                }
                tmpTXbufftill = (tmpTXbufftill + 1) % TX_CAN1_BUFFER_SIZE; // increment tmpTXbufftill
            }

            TXCAN1buff[TXCAN1buffHead].msgID   = msgID;
            TXCAN1buff[TXCAN1buffHead].msgConf = msgCnf;
            TXCAN1buff[TXCAN1buffHead].msgSize = msgSize;
            for (uint8_t i = 0; i < msgSize; ++i)
            {
                TXCAN1buff[TXCAN1buffHead].aData[i] = aData[i];
            }
            TXCAN1buffHead = (TXCAN1buffHead + 1) % TX_CAN1_BUFFER_SIZE; // increment TXCAN1buffHead
        }
    }

    return HAL_OK;
}

#ifdef __EXTENDED_CAN_ACTIVATE
HAL_StatusTypeDef CAN1bus_ExtendedSendData(uint32_t msgID, size_t msgSize, uint8_t aData[])
{
    CAN_TxHeaderTypeDef tmpTxHeader;
    uint8_t tmpData[8];
    uint32_t mailboxNumber; // number of used mailb - kničemu

    tmpTxHeader.ExtId              = msgID;        // ID
    tmpTxHeader.IDE                = CAN_ID_EXT;   // 11 bit ID
    tmpTxHeader.RTR                = CAN_RTR_DATA; // send data or request
    tmpTxHeader.DLC                = msgSize;      // size of message
    tmpTxHeader.TransmitGlobalTime = DISABLE;      //!!!!
    for (uint8_t i = 0; i < msgSize; ++i)
    {
        tmpData[i] = aData[i];
    } // write msg to mailbox
    if (HAL_CAN_AddTxMessage(defineCAN1, &tmpTxHeader, tmpData, &mailboxNumber) != HAL_OK)
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}
#endif //__EXTENDED_CAN_ACTIVATE

#ifdef _DUAL_CAN_ACTIVATE /*--CAN2 Send--*/
HAL_StatusTypeDef CAN2bus_SendData(uint16_t msgID, size_t msgSize, uint16_t msgCnf, uint8_t aData[])
{
    if (HAL_CAN_GetTxMailboxesFreeLevel(defineCAN2) != 0)
    { // Check that all the Tx mailboxes are not full

        CAN_TxHeaderTypeDef tmpTxHeader;
        uint8_t tmpData[8];
        uint32_t mailboxNumber; // number of used mailb - kničemu

        tmpTxHeader.StdId              = msgID;                   // ID
        tmpTxHeader.IDE                = CAN_ID_STD;              // 11 bit ID
        tmpTxHeader.RTR                = msgCnf & CAN_RTR_REMOTE; // send data or request
        tmpTxHeader.DLC                = msgSize;                 // size of message
        tmpTxHeader.TransmitGlobalTime = DISABLE;                 //!!!!
        for (uint8_t i = 0; i < msgSize; ++i)
        {
            tmpData[i] = aData[i];
        } // write msg to mailbox
        if (HAL_CAN_AddTxMessage(defineCAN2, &tmpTxHeader, tmpData, &mailboxNumber) != HAL_OK)
        {
            return HAL_ERROR;
        }
    }
    else
    { // write msg to buffer
        if (((TXCAN2buffHead + 1) % TX_CAN2_BUFFER_SIZE) == TXCAN2buffTill)
        { // if buffer is full
            return HAL_BUSY;
        }
        else
        {

            uint8_t tmpTXbufftill = TXCAN2buffTill;
            while (tmpTXbufftill != TXCAN2buffHead)
            {
                if (TXCAN2buff[tmpTXbufftill].msgID == msgID)
                { // if buff id agree with new id
                    if ((msgCnf & CANdef_ALLMSG) == 0)
                    {                                                   // if selected send only new msg
                        TXCAN2buff[tmpTXbufftill].msgConf |= TXBUFF_NO; // deactivate msg
                    }
                }
                tmpTXbufftill = (tmpTXbufftill + 1) % TX_CAN2_BUFFER_SIZE; // increment tmpTXbufftill
            }

            TXCAN2buff[TXCAN2buffHead].msgID   = msgID;
            TXCAN2buff[TXCAN2buffHead].msgConf = msgCnf;
            TXCAN2buff[TXCAN2buffHead].msgSize = msgSize;
            for (uint8_t i = 0; i < msgSize; ++i)
            {
                TXCAN2buff[TXCAN2buffHead].aData[i] = aData[i];
            }
            TXCAN2buffHead = (TXCAN2buffHead + 1) % TX_CAN2_BUFFER_SIZE; // increment TXCAN2buffHead
        }
    }

    return HAL_OK;
}
#endif

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
    if (hcan->Instance == defineCAN1->Instance)
    {
        CAN1bus_ReadProcessFIFO0(); // call Read function
    }
#ifdef _DUAL_CAN_ACTIVATE
    else if (hcan->Instance == defineCAN2->Instance)
    {
        CAN2bus_ReadProcessFIFO0(); // call Read function
    }
#endif //_DUAL_CAN_ACTIVATE
}

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef* hcan)
{
    if (hcan->Instance == defineCAN1->Instance)
    {
        CAN1bus_ReadProcessFIFO0(); // call Read function
    }
#ifdef _DUAL_CAN_ACTIVATE
    else if (hcan->Instance == defineCAN2->Instance)
    {
        CAN2bus_ReadProcessFIFO0(); // call Read function
    }
#endif //_DUAL_CAN_ACTIVATE
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
    if (hcan->Instance == defineCAN1->Instance)
    {
        CAN1bus_ReadProcessFIFO1(); // call Read function
    }
#ifdef _DUAL_CAN_ACTIVATE
    else if (hcan->Instance == defineCAN2->Instance)
    {
        CAN2bus_ReadProcessFIFO1(); // call Read function
    }
#endif //_DUAL_CAN_ACTIVATE
}

/**
 * @brief Interrupt callback functions when send all msg from mailbox
 */
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef* hcan)
{ // Interrupt, when sand all msg in mailbox
    if (hcan->Instance == defineCAN1->Instance)
    {

#ifdef __EXTENDED_CAN_ACTIVATE
        if (ExtendEnable == 0)
        {
#endif //__EXTENDED_CAN_ACTIVATE

            if (TXCAN1buffHead != TXCAN1buffTill)
            { // add msg from buffer to mailbox
                while ((TXCAN1buff[TXCAN1buffTill].msgConf & TXBUFF_NO) != 0)
                {                                                                // if message is unnecessary
                    TXCAN1buffTill = (TXCAN1buffTill + 1) % TX_CAN1_BUFFER_SIZE; // increment TXCAN1buffTill
                    if (TXCAN1buffHead == TXCAN1buffTill)
                    { // možná že je zbytečná
                        return;
                    }
                }
                CAN_TxHeaderTypeDef tmpTxHeader;
                uint8_t tmpData[8];
                uint32_t mailboxNumber; // number of used mailb - kničemu

                tmpTxHeader.StdId              = TXCAN1buff[TXCAN1buffTill].msgID;                    // ID
                tmpTxHeader.IDE                = CAN_ID_STD;                                          // 11 bit ID
                tmpTxHeader.RTR                = TXCAN1buff[TXCAN1buffTill].msgConf & CAN_RTR_REMOTE; // send data or request
                tmpTxHeader.DLC                = TXCAN1buff[TXCAN1buffTill].msgSize;                  // size of message
                tmpTxHeader.TransmitGlobalTime = DISABLE;                                             //!!!!
                for (uint8_t i = 0; i < TXCAN1buff[TXCAN1buffTill].msgSize; ++i)
                {
                    tmpData[i] = TXCAN1buff[TXCAN1buffTill].aData[i];
                } // write msg to mailbox

                if (HAL_CAN_AddTxMessage(defineCAN1, &tmpTxHeader, tmpData, &mailboxNumber) != HAL_OK)
                {
                    return;
                }
                TXCAN1buffTill = (TXCAN1buffTill + 1) % TX_CAN1_BUFFER_SIZE; // increment TXCAN1buffTill
            }
#ifdef __EXTENDED_CAN_ACTIVATE
        }
#endif //__EXTENDED_CAN_ACTIVATE
    }

#ifdef _DUAL_CAN_ACTIVATE
    else if (hcan->Instance == defineCAN2->Instance)
    {
        if (TXCAN2buffHead != TXCAN2buffTill)
        { // add msg from buffer to mailbox
            while ((TXCAN2buff[TXCAN2buffTill].msgConf & TXBUFF_NO) != 0)
            {                                                                // if message is unnecessary
                TXCAN2buffTill = (TXCAN2buffTill + 1) % TX_CAN2_BUFFER_SIZE; // increment TXCAN2buffTill
                if (TXCAN2buffHead == TXCAN2buffTill)
                { // možná že je zbytečná
                    return;
                }
            }
            CAN_TxHeaderTypeDef tmpTxHeader;
            uint8_t tmpData[8];
            uint32_t mailboxNumber; // number of used mailb - kničemu

            tmpTxHeader.StdId              = TXCAN2buff[TXCAN2buffTill].msgID;                    // ID
            tmpTxHeader.IDE                = CAN_ID_STD;                                          // 11 bit ID
            tmpTxHeader.RTR                = TXCAN2buff[TXCAN2buffTill].msgConf & CAN_RTR_REMOTE; // send data or request
            tmpTxHeader.DLC                = TXCAN2buff[TXCAN2buffTill].msgSize;                  // size of message
            tmpTxHeader.TransmitGlobalTime = DISABLE;                                             //!!!!
            for (uint8_t i = 0; i < TXCAN2buff[TXCAN2buffTill].msgSize; ++i)
            {
                tmpData[i] = TXCAN2buff[TXCAN2buffTill].aData[i];
            } // write msg to mailbox

            if (HAL_CAN_AddTxMessage(defineCAN2, &tmpTxHeader, tmpData, &mailboxNumber) != HAL_OK)
            {
                return;
            }
            TXCAN2buffTill = (TXCAN2buffTill + 1) % TX_CAN2_BUFFER_SIZE; // increment TXCAN2buffTill
        }
    }
#endif //_DUAL_CAN_ACTIVATE
}
