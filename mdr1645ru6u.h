#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL
#include "mdr32f8_port.h"               // Keil::Drivers:PORT


void RAM_Addr_Set(uint32_t Cell_Addr); // set ram addr

//write data bits to ram 
void ram_write( uint32_t cell_addr, uint16_t *Template);



//read data bits from ram
void ram_read(uint32_t cell_addr, uint16_t *Read_Array);

//Compare Read_Array (ram_data) and Template (Pattern)
uint64_t compare_data(uint16_t pattern[8], uint16_t ram_data[8],uint32_t cell_addr);