
#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL
#include "mdr32f8_port.h"               // Keil::Drivers:PORT
#include <stdlib.h>
#include "ram_macros.h"
#include "mdr1645ru6u.h"

//Needed For Data Tranfer
uint32_t RAM_1_Data_Bus[16] ={ R1D0, R1D1, R1D2, R1D3, R1D4, R1D5, R1D6, R1D7, R1D8, R1D9, R1D10, R1D11, R1D12, R1D13, R1D14, R1D15};                                                               
uint32_t RAM_2_Data_Bus[16] ={ R2D0, R2D1, R2D2, R2D3, R2D4, R2D5, R2D6, R2D7, R2D8, R2D9, R2D10, R2D11, R2D12, R2D13, R2D14, R2D15};                                                               
uint32_t RAM_3_Data_Bus[16] ={ R3D0, R3D1, R3D2, R3D3, R3D4, R3D5, R3D6, R3D7, R3D8, R3D9, R3D10, R3D11, R3D12, R3D13, R3D14, R3D15};                                                               
uint32_t RAM_4_Data_Bus[16] ={ R4D0, R4D1, R4D2, R4D3, R4D4, R4D5, R4D6, R4D7, R4D8, R4D9, R4D10, R4D11, R4D12, R4D13, R4D14, R4D15};                                                               
uint32_t RAM_5_Data_Bus[16] ={ R5D0, R5D1, R5D2, R5D3, R5D4, R5D5, R5D6, R5D7, R5D8, R5D9, R5D10, R5D11, R5D12, R5D13, R5D14, R5D15};                                                               
uint32_t RAM_6_Data_Bus[16] ={ R6D0, R6D1, R6D2, R6D3, R6D4, R6D5, R6D6, R6D7, R6D8, R6D9, R6D10, R6D11, R6D12, R6D13, R6D14, R6D15};                                                               
uint32_t RAM_7_Data_Bus[16] ={ R7D0, R7D1, R7D2, R7D3, R7D4, R7D5, R7D6, R7D7, R7D8, R7D9, R7D10, R7D11, R7D12, R7D13, R7D14, R7D15};                                                               
uint32_t RAM_8_Data_Bus[16] ={ R8D0, R8D1, R8D2, R8D3, R8D4, R8D5, R8D6, R8D7, R8D8, R8D9, R8D10, R8D11, R8D12, R8D13, R8D14, R8D15};  
uint32_t RAM_1_8_Addr_Bus[20] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19};
uint32_t ALLRAM_Data_Serial_Bus[128] = {R1D0, R1D1, R1D2, R1D3, R1D4, R1D5, R1D6, R1D7, R1D8, R1D9, R1D10, R1D11, R1D12, R1D13, R1D14, R1D15, R2D0, R2D1, R2D2, R2D3, R2D4, R2D5, R2D6, R2D7, R2D8, R2D9, R2D10, R2D11, R2D12, R2D13, R2D14, R2D15, R3D0, R3D1, R3D2, R3D3, R3D4, R3D5, R3D6, R3D7, R3D8, R3D9, R3D10, R3D11, R3D12, R3D13, R3D14, R3D15, R4D0, R4D1, R4D2, R4D3, R4D4, R4D5, R4D6, R4D7, R4D8, R4D9, R4D10, R4D11, R4D12, R4D13, R4D14, R4D15, R5D0, R5D1, R5D2, R5D3, R5D4, R5D5, R5D6, R5D7, R5D8, R5D9, R5D10, R5D11, R5D12, R5D13, R5D14, R5D15, R6D0, R6D1, R6D2, R6D3, R6D4, R6D5, R6D6, R6D7, R6D8, R6D9, R6D10, R6D11, R6D12, R6D13, R6D14, R6D15, R7D0, R7D1, R7D2, R7D3, R7D4, R7D5, R7D6, R7D7, R7D8,R7D9, R7D10, R7D11, R7D12, R7D13, R7D14, R7D15, R8D0, R8D1, R8D2, R8D3, R8D4, R8D5, R8D6, R8D7, R8D8, R8D9, R8D10, R8D11, R8D12, R8D13, R8D14, R8D15};
//Addres Set
void RAM_Addr_Set(uint32_t Cell_Addr)
{
	for (uint32_t i=0; i<20; i++)
		{
			PORTA->SOE=1;
			if(((Cell_Addr>>i) & 1<<0)==1<<0)
			{
				PORT_SetBits(PORTA, RAM_1_8_Addr_Bus [i]);
			}
			else
			{
				PORT_ResetBits(PORTA, RAM_1_8_Addr_Bus [i]);
			}
		}
}				



//write data to specific cell in each ram

void RAM_write( uint32_t cell_addr, uint16_t *Template)
{
/*OE    ______/---------\_______	
	ADDR  
	*/
	
	
	
	
	PortControl* Port_Used = (PortControl *) ((uint32_t) (0x40081000)); // For PORTx invokes
	PORT_SetBits (PORTA, NOE); 									//RAM Data inputs enter Z state
	PORTB->SOE=1;	
	PORTC->SOE=1;	
	PORTD->SOE=1;	
	PORTE->SOE=1;	
	

	RAM_Addr_Set(cell_addr); 										//Set Cell Addr

	PORT_ResetBits (PORTA, NOE ); 							//Drop nOE (pull to 0)
	PORT_ResetBits (PORTA, NWE);					      //Drop nWe to 0 
	for (uint8_t j=0; j<8; j++)
	{
		for (uint8_t i = 0; i<16; i++)
		{
			if (((Template [j])>>i & 1) == 1)
				PORT_SetBits(Port_Used, ALLRAM_Data_Serial_Bus[j*16 + i]);
			else
				PORT_ResetBits(Port_Used, ALLRAM_Data_Serial_Bus[j*16 + i]);
		}
	if (j%2==1) 
		Port_Used+=0x1000;
  }
	PORT_SetBits (PORTA, NWE);											//Pull NWE UP (Write!)
	PORT_SetBits (PORTA, NOE);											//Turn it off
}

//
void RAM_read(uint32_t cell_addr, uint16_t *Read_Array)
{
	PortControl* Port_Used = (PortControl *) ((uint32_t) (0x40081000)); // For PORTx invokes
	for (uint8_t i = 0; i<8; i++)
	{
		Read_Array[i] = 0;
	}
	
	PORTB->SOE=0;	
	PORTC->SOE=0;	
	PORTD->SOE=0;	
	PORTE->SOE=0;	
	
	RAM_Addr_Set(cell_addr);																		//set cell address
	PORT_SetBits (PORTA, NWE);
	PORT_ResetBits (PORTA, NCE);
	PORT_ResetBits (PORTA, NOE);
	for (uint8_t j=0; j<8; j++)																	//Read All Ram Data
	{
		for (uint8_t i=0; i<16; i++)
		{
			Read_Array[j]=( Read_Array[j]+(((uint16_t)( PORT_ReadInputDataBit (Port_Used, RAM_1_8_Addr_Bus[16*j + i]) ) ) <<i) );
		}
		if (j%2==1)
			Port_Used+=0x1000;
	}
	PORT_SetBits(PORTA, NOE);												//Pull Control Signals Up
}
//Fill All RAMs 
void Ram_Fill( uint16_t *Template)
{
	uint32_t Cell_Addr;
	for (Cell_Addr=0 ; Cell_Addr<(1<<20); Cell_Addr++)
	{
		RAM_write (Cell_Addr, Template);
	}
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

void 

