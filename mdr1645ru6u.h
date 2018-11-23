#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL
#include "mdr32f8_port.h"               // Keil::Drivers:PORT



//write data bits to ram 
void ram_write(uint16_t ram_data);



//read data bits from ram
uint16_t ram_read(PortControl* data_port,uint8_t read_bits,uint32_t cell_addr);


uint64_t compare_data(uint16_t pattern[8], uint16_t ram_data[8],uint32_t cell_addr);