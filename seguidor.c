/******************************************************************************/
/**        Proyecto SED: 4 Fantásticos & Dios                               **/
/**                                                                          **/
/**       Comunicación Bluetooth Ordenador-Automóvil mediante PIC            **/
/**                                                                          **/ 
/**         Miembros 4 Fantásticos: Borja, Benito, Mario, Pablo              **/
/**                        Copyright (C) 2013                                **/
/******************************************************************************/
#define VERSION 0.0.1
#include <18f4520.h>
#device ADC=10

/*----------------------------------------------------------------------------*/
/*-             Configuración de módulos del microcontrolador                -*/
/*----------------------------------------------------------------------------*/
#use delay(clock=1MHz)  // CHECK: Mejor usamos 8Mhz 
#use rs232(baud=9600, uart1) 
#define PERIODO_TIMER2      255      // Equivale a 18.4 ms (aprox.)

/*----------------------------------------------------------------------------*/
/*-                            Variables                                     -*/
/*----------------------------------------------------------------------------*/

int16 CDER,CIZQ;

/*----------------------------------------------------------------------------*/
/*-                         Bits de configuración                            -*/
/*----------------------------------------------------------------------------*/
#FUSES NOWDT        // Perro guardían desactivado
#FUSES INTRC        // Reloj interno del micro
#FUSES PUT          // Delay de inicio para asegurar estabilidad
#FUSES NOPROTECT    // Protección de código desactivada
#FUSES NOBROWNOUT   // Reinicio por caída de voltaje desactivado
#FUSES LVP          // ¡NO CAMBIAR! Habilita la programación en bajo voltaje

void main(){

  setup_oscillator(OSC_1MHz);
  
  set_tris_a(0x00);   //pines de entrada de valores analogicos
  
  //para que el coche se redirija solo
  setup_timer_2(T2_DIV_BY_16, PERIODO_TIMER2, 4);
  setup_ccp1(CCP_PWM);
  setup_ccp2(CCP_PWM);
  setup_adc_ports(AN0_TO_AN1);
  setup_adc(adc_clock_div_2);   //comprobar segun el pic
  setup_uart(9600);
  delay_us(10);
  
  while(true){
  
    set_adc_channel(0);
    delay_us(10);
    CDER = read_adc();
    set_adc_channel(1);
    delay_us(10);
    CIZQ = read_adc();
    
    if (CDER == CIZQ){
      CCP_1_LOW = 15;
      CCP_2_LOW = 32;
    }
    else{
      if (CDER > CIZQ){
        CCP_1_LOW = 23;
        CCP_2_LOW = 32;
      }
      else{
        CCP_1_LOW = 32;
        CCP_2_LOW = 23;
      }
    }
  }
}
    
  
  
