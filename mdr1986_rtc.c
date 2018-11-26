#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL
#include "mdr1986_rtc.h"              




void RTC_Init(void)
{
	
	//configure clock source
	BKPCNTR_REG_63_TMRx_LSIcmd(ENABLE);
	//lsi output freq 40 khz
	
	
	BKP->KEY=0x8555AAA1; //bkp registers write enable
	
	BKP->REG_63_TMR0 = 1<<31; //rtc reset 
	BKP->REG_63_TMR1 = 1<<31;
	BKP->REG_63_TMR2 = 1<<31;
	

	
	BKP->RTC_DIV_TMR0 = 40000;	 //prescaler, target frequency = 1 hz
	BKP->RTC_DIV_TMR1 = 40000;
	BKP->RTC_DIV_TMR2 = 40000;
	
//	BKP->RTC_PRL_TMR0 = 40000;	//ili eto prescaler, ya ne ochen ponyal
//	BKP->RTC_PRL_TMR1 = 40000;
//	BKP->RTC_PRL_TMR2 = 40000;
	
	BKP->REG_63_TMR0 = (0<<31) | (1<<3);   //reset bit =0, rtc enable, clock source - low speed internal
	BKP->REG_63_TMR1 = (0<<31) | (1<<3);   
	BKP->REG_63_TMR2 = (0<<31) | (1<<3); 
	
	
	
	BKP->KEY=0x00000000; //bkp registers write disable
	
}



void RTC_LoadValue(uint32_t preload)
{
	
	BKP->KEY=0x8555AAA1; //bkp registers write enable

	BKP->RTC_CNT_TMR0 = preload; //set rtc preload
	BKP->RTC_CNT_TMR1 = preload;
	BKP->RTC_CNT_TMR2 = preload;
	
	BKP->KEY=0x00000000; //bkp registers write disable
}


uint32_t RTC_GetValue(void)
{
	uint32_t retval;
	retval=BKP->RTC_CNT_TMR0; //read from main counter register
	return retval;

}