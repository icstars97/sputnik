#include "mdr1645ru6u.h"
#include "mdr1986_rtc.h"
#include <stdlib.h>
#include "mdr1645_failreport.h"






uint32_t* compare_data(uint16_t pattern[8],uint16_t ram_data[8],uint32_t cell_addr)
{
	uint8_t i,j=0,k=0,failcount=0;
	uint16_t offset;
	uint8_t err_num;
	uint32_t* fail_arr;
	fail_arr=(uint32_t*)malloc(2*sizeof(uint32_t));
	fail_arr[0]=RTC_GetTime();
	fail_arr[1]=cell_addr;
	for(i=1;i<=8;i++)
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
void RAM_SaveFailArray(void)
{
}


RAM_FailReport GetFailReport(void)
{
	
	
}