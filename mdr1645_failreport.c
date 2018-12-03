#include "mdr1645ru6u.h"
#include "mdr1986_rtc.h"
#include <stdlib.h>
#include "mdr1645_failreport.h"






uint32_t* build_FailArray(uint16_t pattern[8],uint16_t ram_data[8],uint32_t cell_addr)
{
	uint8_t i,j=0,k=0,failcount=0,errcount=0;;
	uint16_t offset;
	uint8_t err_num;
	uint32_t* fail_arr;
	fail_arr=(uint32_t*)malloc(2*sizeof(uint32_t));
	fail_arr[1]=cell_addr;
	for(i=1;i<9;i++)
		{
			
			if (pattern[i]!=ram_data[i])
			{	
				errcount++;
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
		if (errcount)
		{
			fail_arr[errcount]|=(1<<0);
			fail_arr[0]=RTC_GetTime();
		}else
		{
			fail_arr[1]=0;
		}
			return &fail_arr[0];
}
//storage[0] reserved for report
//			XXXX 		XXXX 		XXXX 		XXXX 		XXXX 		XXXX 		XXXX 		XX00 
//		  |space left      | failure count   |last timestamp number|
uint8_t RAM_SaveFailArray(uint32_t* storage,uint32_t* fail_arr)
{
	uint16_t errcount,index,timestamp_pos,i=1;
	if (((storage[0] & (0x3FF<<22))>>22)<999)
	{
		index=999-((storage[0] & (0x3FF<<22))>>22)+2;
		errcount=(storage[0] & (0x3FF<<12))>>12;
		timestamp_pos=index-1;
		storage[index-1]=fail_arr[0];
		while(!(fail_arr[i] & (1<<0)))
		{
			storage[index]=fail_arr[i];
			i++;
			index++;
			if (fail_arr[i] & (0xF<<1)) errcount+=2;
			else errcount++;
		}
		storage[0]=((999-index)<<22) | (errcount<<12) | (timestamp_pos<<2);
		
	}
	return ((storage[0] & (0x3FF<<22))>>22);
	
}


RAM_FailReport GetFailReport(uint32_t* storage)
{
	RAM_FailReport report;
	report.failcount=(storage[0] & (0x3FF<<12))>>12;
	report.free_space=(storage[0] & (0x3FF<<22))>>22;
	report.last_timestamp=(storage[0] & (0x3FF<<2))>>2;
	return report;
	
	
}
void RAM_StorageClear(uint32_t* storage)
{
		for (int i=0;i<1000;i++)
	{	
		storage[i]=0;
	}
}