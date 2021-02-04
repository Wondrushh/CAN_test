
# Driver: Dragon_CANbus
## Note:
- Zkuste vysmyslet co nejvíc zpráv, ktrá by se mohla posílat. Jelikož ubírat je jednodušší, než přidávat !!


------------

[[_TOC_]]

## Changelog
**Version 2.2**
- **<ins>compatible with version 2.1</ins>**
- add feature for send message with extended ID

**Version 2.1**
- **<ins>compatible with version 2.0</ins>**
- add ID list and fix some bugs

**Version 2.0**
- **<ins>NOT compatible with version 1.0</ins>**
- Enable dual CAN

**Version 1.0**
- Create new librarry 
- Enable only one CAN

## How to use
### CubeMX:
1. Activate CAN peripheral
2. Open [online calculator](http://www.bittiming.can-wiki.info/ "online calculator")
3. Select **ST Microelectronics bxCAN** in the first box
4. Select Clock Rate (not write SYSCLK, but bus clock (APB1))
5. Select bit-rate  1000 kbit/s
6. Copy value **Prescaler** , **Seg 1** and **Seg 2** to CubeMX 
7. Automatic retransmission -> Enable
8. Operate Mode -> Normal
9. Enable Interrupt: **CAN TX** ,  **CAN RX0** and **CAN RX1**
   - or global interrupt for lower STM
 

### Prepare files:
1. Import core files `Dragon_CANbus.c/.h` and file with constants `Dragon_CANbus_filter.c/.h` and check if path is correct
2.  In file `Dragon_CANbus.h` uncomment #include library for current MCU (F0 or F1 ...) 
3. If you wont use DUAL CAN -> uncoment `#define _DUAL_CAN_ACTIVATE` In file `Dragon_CANbus.h`
4. If you wont use full interrupt mode -> uncomment `#define _CAN1def_ONLY_INTERRUPT_MODE` or `#define _CAN2def_ONLY_INTERRUPT_MODE` In file `Dragon_CANbus.h`
5. For change size of TX buffer change a value in `#define TX_CAN1_BUFFER_SIZE` in `Dragon_CANbus.c` file. Range is uint8_t (default is 8)
6. For select CAN bus <ins>uncomment</ins> current line `#define CAN1_CANxxxBUS` in `Dragon_CANbus.h` file.
7. For select CAN bus gate <ins>uncomment</ins> current line `#define __CAN1_FILTERLIST` in `Dragon_CANbus.h` file.
8. If you use DUAL can make step 6. and 7. again for CAN2

### Implementation code:
1. Call init function `CANbus_Init(&hcan)` [for DUAL CAN `CANbus_Init(&hcan1, &hcan2)`]
2. Call filter init function `CANbus_FilterInit()`
3. Insert Start CAN peripheral block: 
```
  if (HAL_CAN_Start(&hcan) != HAL_OK){  
    Error_Handler(); /* Start Error */
  }
```
4. If you use DUAL CAN make step 3. again for CAN2

### Using library for TX:
1. Call transmit function 
```
if (CANXbus_SendData(msgID,msgSize, msgCnf, aData) != HAL_OK){
    Error_Handler();
  }
```
   - X = Number of CAN (allow value: 1 or 2 )
   - msgID = ID
      - Recommended use define name : `CANxxx_ID_yyy` 
      - xxx=CAN bus (gen, crit, ams, inv) 
      - yyy=Name of transmit data
   - msgSize = Size of payload. Number of sizes between 0 and 8. (Can use function `sizeof(aData)`)
   - msgCnf = Specifies the type of msg
      - request/data -> CAN_RTR_REMOTE / CAN_RTR_DATA
      - send all/only new -> CANdef_ALLMSG / CANdef_NEWMSG
      - Example: 
      - `(CAN_RTR_DATA | CANdef_ALLMSG)`  -> send data and send all msg
      - `(CAN_RTR_DATA | CANdef_NEWMSG)`  -> send data and send only new msg
      - `(CAN_RTR_REMOTE | CANdef_ALLMSG)`  -> send request and send all msg
      - `(CAN_RTR_REMOTE | CANdef_NEWMSG)`  -> send request and send only new msg
   - aData = array of payloads. Doesn't matter how array is size.
2. If function `CANxbus_SendData()` return `HAL_BUSY` -> TX buffer is full
3. If you want find out if become ACK error of the last transmission: 
```
if ((hcan.Instance->ESR & CAN_ESR_LEC_Msk) >> CAN_ESR_LEC_Pos) == 0x3){
   //became a ACK error -> maybe CAN connector is broken
  }
```

### Using library for RX:
1. Insetr this code block into infinity while:
```
#ifndef _CAN1def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) != 0){
        //if message pending in Fifo
      CAN1bus_ReadProcessFIFO0();  //read data
    }
#endif //_CAN1def_ONLY_INTERRUPT_MODE
#ifdef _DUAL_CAN_ACTIVATE    
#ifndef _CAN2def_ONLY_INTERRUPT_MODE
    if (HAL_CAN_GetRxFifoFillLevel(&hcan3, CAN_RX_FIFO0) != 0){
        //if message pending in Fifo
      CAN2bus_ReadProcessFIFO0();  //read data
    }
#endif //_CAN2def_ONLY_INTERRUPT_MODE
#endif  //_DUAL_CAN_ACTIVATE
```
2. For enable *full-interrupt mode* uncomment #define `_CAN1def_ONLY_INTERRUPT_MODE` or `_CAN2def_ONLY_INTERRUPT_MODE` in file `Dragon_CANbus.h`
3. For activate callback function must add define to file `Dragon_CANbus.h`. Available sentence can find in `Dragon_CANbus_filter.h`. 
   - Example `#define _CANgen_USED_TEMPERATURE`

 

4. Implement callback function into user file. Example:
```
  void CANfunc_temperature(uint8_t aPayload[]){   //callback function
    //do somethings
  }
``` 
Available sentence can find in `Dragon_CANbus_filter.c` file. Name of function started with `__weak` werb

- try it write callback function to shortest
- **!! DON'T FORGET IMPLEMENT CALLBACK OR DISABLE CALLBACK !!**

### Using library for extended ID message:
1. Uncomment `#define __EXTENDET_CAN_ACTIVATE` in file `Dragon_CANbus.h`
2. Include init extended func. `CANbus_ExtendetFilterInit()` between `CANbus_FilterInit()` and `HAL_CAN_Start()`
- Extended methd use only CAN1
- CAN filter is disable and pass all IDs

3. For send message use 
```
CAN1bus_ExtendetSendData(uint32_t msgID, size_t msgSize, uint8_t aData[]){
```
   - msgID = ID
      - You must write <ins>number</ins> not define constant
   - msgSize = Size of payload. Number of sizes between 0 and 8. (Can use function `sizeof(aData)`)
   - aData = array of payloads. Doesn't matter how array is size.
4. Insert callback function into user file.
```
void _CANext_func_callback(uint8_t aPayload[], uint32_t IDmsg){
  //some code
}
```

### Using library misc:
- HW requirement: 8KB FLASH memory
- test with osciloscope: 8B message  1Mb/s  == +-57us
- IF YOU DON'T UNDERSTAND SOMETHINGS, TELL ME, NOT SPEND THE TIME
------------
