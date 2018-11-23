//RAM -- port A pins define

//RAM control pins -- port A pins(27-31)
//#define BHE 0x8000U<<16 
//#define BLE 0x4000U<<16 
//#define WE 	0x2000U<<16
//#define CE 	0x1000U<<16
//#define OE 	0x0800U<<16
#define RAM_STORE 0x1000U<<16
#define RAM_WRITE 0x0000U<<16
#define RAM_READ 	0x2000U<<16
#define RAM_CONTROL_PINS 0xF800U<<16



//RAM address  pins -- port A pins(0-19)
#define RAM_ADDR_HI 0x000FU<<16
#define RAM_ADDR_LO 0xFFFFU