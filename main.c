/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
int adcConvertido;
int volts = 0;
int adcConvertidoR = 0, adcConvertidoIR = 0;
char saida[50];
    
CY_ISR(rotina){
    
   //vermelho 
   Pin_vermelho_Write(1);
   Pin_infravermelho_Write(0); 
   ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
   adcConvertidoR = (ADC_GetResult16(0));     
   volts = (ADC_CountsTo_mVolts(0,adcConvertido));   
   UART_UartPutString(saida); 
   CyDelay(100);

   //infra vermelho
   Pin_vermelho_Write(0);
   Pin_infravermelho_Write(1); 
   ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
   adcConvertidoIR = (ADC_GetResult16(0));        
   volts = (ADC_CountsTo_mVolts(0,adcConvertido));

   sprintf(saida,"%d %d\n",adcConvertidoIR,adcConvertidoR);     
   UART_UartPutString(saida); 
   Timer_1_ClearInterrupt(Timer_1_INTR_MASK_CC_MATCH);
}

int main(void)
{
    CyGlobalIntEnable;
    
    Opamp_1_Start();
    UART_Start();
    ADC_Start();
    ADC_StartConvert();
    Timer_1_Start();
    isr_1_StartEx(rotina);
    
    for(;;)
    {

    }
}

/* [] END OF FILE */