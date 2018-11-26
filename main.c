


#include "MDR1986VE8T.h"
#include "mdr32f8_clkctrl.h"            // Keil::Drivers:CLKCTRL
#include "mdr32f8_port.h"   						// Keil::Drivers:PORT
#include "ram_macros.h"									//ram pin/command macros file
#include "mdr1645ru6u.h"								//ram functions header file
//port A initialization structure
PORT_InitTypeDef PORT_InitStruct;

int main(void)
{

//clock configuration, target frequency 60MHz
//reset clock settings to default
CLKCTRL_DeInit();
//enable high-speed internal clock generator
BKPCNTR_REG_63_TMRx_HSIcmd(ENABLE);
//configure clock source and frequency prescaler
CLKCTRL_MAX_CLKSelection(CLKCTRL_MAX_CLK_PLL0);
//q=0,n=8 freq=64MHz
CLKCTRL_CPU_PLLconfig(PLL0, CLKCTRL_PLLn_CLK_SELECT_HSIdiv1 , 0 , 8);
//configure periphery clock
CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_PORTA_EN	, ENABLE); //port A
CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_PORTB_EN	, ENABLE); //port B
CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_PORTC_EN	, ENABLE); //port C
CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_PORTD_EN	, ENABLE); //port D
CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_PORTE_EN	, ENABLE); //port E
	
//configure port A-E

////port A
////pins select
//PORT_InitStruct.PORT_Pin = RAM_CONTROL_PINS | RAM_ADDR_HI | RAM_ADDR_LO;
////configure input mode/output mode
//PORT_InitStruct.PORT_SOE = PORT_SOE_OUT;
////configure output type
//PORT_InitStruct.PORT_SANALOG = PORT_SANALOG_DIGITAL;
////configure driver mode
//PORT_InitStruct.PORT_SPD = PORT_SPD_OFF;
////configure port speed(eto po suti dlitelnost frontov impulsa)
//PORT_InitStruct.PORT_SPWR = PORT_SPWR_300; //ne uveren chto suda peredavat, pust poka dlitelnost maksimalnaya budet
////port A intialization
//PORT_Init(PORTA, &PORT_InitStruct);
// 
//PORT_SetBits(PORTA, RAM_STORE ); //ram output disabled, storage mode

while(1)
{
	

	
	
	
	
	
	
	
	
	
	
	
	
}
}