//****** Universidade Tecnol�gica Federal do Paran� - UTFPR     ******\\
//****** Engenharia Eletr�nica - DAELN                          ******\\
//****** Sistemas embarcados - Professor: Hugo Vieira Neto      ******\\
//****** Aluno: Bruno Soares de Souza 1558781                   ******\\
// Pr�tica 1:

#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

uint8_t LED_D4 = 0;

void main(void){

  SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 24000000); // 24MHz
//  SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSB9DCTL_CFG_VCO_320, 120000000); // 120MHz

// Quando configuramos o delay para 24MHz, se aumentarmos a frequ�ncia do clock
// faz o "segundo" passar mais r�pido
// em 24MHz, precisa-se de 8*10^6 ciclos do systick para 1 segundo
  
//// Dado que: 1/24MHz = 41.7ns (4.17*10^-8s), e para cada ciclo do systcick (3 instru��es) temos 125ns
//// a� finalmente 1s/125ns = 8*10^6 ciclos
  
////// Usando 120MHz:
//////  Temos 8.33ns , vezes 3 isntru��es: 25.0ns resultando em 4*10^7 ciclos (menos ciclos para 1 segundo)
  
  
////////  Configura��es diferentes de otimiza��o n�o surtiram efeito percept�vel
    
    
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilita��o
      
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // LED D4 como sa�da
  
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // LED D4 apagado
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  

  SysTickIntEnable();
  SysTickEnable();

  while(1){
    
      SysCtlDelay(8000000);

  LED_D4 ^= GPIO_PIN_0; // Troca estado do LED D4
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, LED_D4); // Acende ou apaga LED D4b9D

  } // while
} // main