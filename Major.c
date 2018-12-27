#include <stdlib.h>
#include "MDR1986VE8T.h"

void Triple_Write ( uint32_t Data_To_Write,  uint32_t *PlaceToWrite)
{
	for (uint8_t i=0; i<3; i++)
		{
			PlaceToWrite[i]=Data_To_Write;
		}
}

uint32_t Triple_Read (uint32_t *PlaceToRead)
{
	uint8_t Amount_of_1=0;
	uint32_t Read_Value=0;
	for(uint8_t i=0; i<32; i++)
	{
		for(uint8_t j=0; j<3; j++)
		{
			if ((PlaceToRead[j]>>i & 1 )==1) 
				Amount_of_1++;
		}
		if (Amount_of_1>1) 
			Read_Value = Read_Value + (1<<i);
		Amount_of_1 = 0;
	}
	Triple_Write ( Read_Value, PlaceToRead);
	return Read_Value;
}
