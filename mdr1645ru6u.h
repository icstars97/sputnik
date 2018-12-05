#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL
#include "mdr32f8_port.h"               // Keil::Drivers:PORT




//write data bits to ram 
void RAM_write( uint32_t cell_addr, uint16_t *Template);

//Set Addres
void RAM_Addr_Set(uint32_t Cell_Addr);

//read data bits from ram
void RAM_read(uint32_t cell_addr, uint16_t *Read_Array);

