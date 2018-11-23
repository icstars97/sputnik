
#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL
#include "mdr32f8_port.h"               // Keil::Drivers:PORT
#include "ram_macros.h"									//ram pin/command macros file
#include <stdlib.h>
typedef struct 
{
	uint16_t pb_hi,pb_lo,pc_hi,pc_lo,pd_hi_pd_lo,pd_hi,pd_lo,pe_hi,pe_lo;
	
	
}ramdata;








//write data bits to ram
void ram_write(ramdata write_bits,uint32_t cell_addr)
{
	PORTB->SOE=1;	
	PORTC->SOE=1;	
	PORTD->SOE=1;	
	PORTE->SOE=1;	
	
	PORT_SetBits (PORTA, RAM_WRITE | cell_addr ); 				//set cell address
	PORT_SetBits (PORTB,write_bits.pb_hi<<16);						//write data bits to all crystals
	PORT_SetBits (PORTB,write_bits.pb_lo);
	PORT_SetBits (PORTC,write_bits.pc_hi<<16);
	PORT_SetBits (PORTC,write_bits.pc_lo);
	PORT_SetBits (PORTD,write_bits.pd_hi<<16);
	PORT_SetBits (PORTD,write_bits.pd_lo);
	PORT_SetBits (PORTE,write_bits.pe_hi<<16);
	PORT_SetBits (PORTE,write_bits.pe_lo);
	PORT_SetBits (PORTA,RAM_STORE);												//ram back to storage mode
	PORT_SetBits (PORTB,0x0000U);											//reset data bits 
	PORT_SetBits (PORTC,0x0000U);	
	PORT_SetBits (PORTD,0x0000U);	
	PORT_SetBits (PORTE,0x0000U);	
}

//read data bits from ram, read_bits 1 to read higher bits, 0 to read lower
ramdata ram_read(uint32_t cell_addr)
{
	ramdata ram_in;
	PORTB->SOE=0;	
	PORTC->SOE=0;	
	PORTD->SOE=0;	
	PORTE->SOE=0;	
	
	PORT_SetBits (PORTA, RAM_READ| cell_addr ); 	//set cell address

		ram_in.pb_hi=(uint16_t)((PORTB->RXTX) >> 16);							//read data bits to all crystals
		ram_in.pb_lo=(uint16_t)((PORTB->RXTX) & 0x0000FFFFU);
		ram_in.pc_hi=(uint16_t)((PORTC->RXTX) >> 16);				
		ram_in.pc_lo=(uint16_t)((PORTC->RXTX) & 0x0000FFFFU);
		ram_in.pd_hi=(uint16_t)((PORTD->RXTX) >> 16);				
		ram_in.pd_lo=(uint16_t)((PORTD->RXTX) & 0x0000FFFFU);
		ram_in.pe_hi=(uint16_t)((PORTE->RXTX) >> 16);				
		ram_in.pe_lo=(uint16_t)((PORTE->RXTX) & 0x0000FFFFU);
		
		PORT_SetBits (PORTA,RAM_STORE);												//ram back to storage mode
		return ram_in;
	
	
	
}
uint32_t* compare_data(uint16_t pattern[8],uint16_t ram_data[8],uint32_t cell_addr)
{
	uint8_t i,j=0,k=0,failcount=0;
	uint16_t offset;
	uint8_t err_num;
	uint32_t* fail_arr;
	fail_arr=(uint32_t*)malloc(sizeof(uint32_t));
	fail_arr[0]=cell_addr;
	for(i=0;i<8;i++)
		{
			
			if (pattern[i]!=ram_data[i])
			{	
				fail_arr[k]=(fail_arr[k]<<4) | i;
		
				offset=pattern[i] ^ ram_data[i];
				
				while(offset)
				{	
					if (failcount==2) 
					{
						fail_arr=(uint32_t*)realloc(fail_arr,(sizeof(uint32_t))*(k+1));
						k++;
						failcount=0;
						fail_arr[k]=fail_arr[k-1]>>8;
						
					}
					if (offset & (1<<0)) 
					{
						failcount++;
						err_num=j;
					}
					j++;
					offset=offset>>1;
				
					fail_arr[k]=(fail_arr[k]<<4) | err_num;
				
					
				}
			failcount=0;
			j=0;	
			fail_arr=(uint32_t*)realloc(fail_arr,(sizeof(uint32_t))*(k+1));
			k++;
			fail_arr[k]=cell_addr;
			}	
		}	
		return &fail_arr[0];
}

