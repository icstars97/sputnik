

typedef struct{
	
	uint16_t failcount; // total ram failure count
	uint16_t last_timestamp; // timestamp of last failures registered
	uint16_t measurements;  // measurements count (number of series with failures)
	
	
	
	
	
	
	
	
}RAM_FailReport;




uint32_t* build_FailArray(uint16_t pattern[8],uint16_t ram_data[8],uint32_t cell_addr); //compare data extracted from RAM with data in template


uint8_t RAM_SaveFailArray(uint32_t* storage,uint32_t* fail_arr); //save failure array to failure storage

void RAM_StorageClear(uint32_t* storage); //clear failure storage