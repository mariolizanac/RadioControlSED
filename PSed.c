/******************************************************************************/
/**        Proyecto SED: 4 Fantásticos | Special Guest: Vicente              **/
/**                                                                          **/
/**       Comunicación Bluetooth Ordenador-Automóvil mediante PIC            **/
/**                                                                          **/ 
/**         Miembros 4 Fantásticos: Borja, Benito, Mario, Pablo              **/
/**                        Copyright (C) 2013                                **/
/******************************************************************************/
#define VERSION 0.0.1
#include <18f4520.h>

/*----------------------------------------------------------------------------*/
/*-             Configuración de módulos del microcontrolador                -*/
/*----------------------------------------------------------------------------*/
#use delay(clock=1MHz)  // CHECK: Mejor usamos 8Mhz 
#use rs232(baud=9600, uart1) 

/*----------------------------------------------------------------------------*/
/*-                         Bits de configuración                            -*/
/*----------------------------------------------------------------------------*/
#FUSES NOWDT        // Perro guardían desactivado
#FUSES INTRC        // Reloj interno del micro
#FUSES PUT          // Delay de inicio para asegurar estabilidad
#FUSES NOPROTECT    // Protección de código desactivada
#FUSES NOBROWNOUT   // Reinicio por caída de voltaje desactivado
#FUSES LVP          // ¡NO CAMBIAR! Habilita la programación en bajo voltaje

/*----------------------------------------------------------------------------*/
/*-                             Constantes                                   -*/
/*----------------------------------------------------------------------------*/
#define PIN_LED_ENCENDIDO   PIN_A1
#define PERIODO_TIMER2      255      // Equivale a 18.4 ms (aprox.)

/*----------------------------------------------------------------------------*/
/*-                             Recibido                                     -*/
/*----------------------------------------------------------------------------*/
char Recibido = 'p';

/*----------------------------------------------------------------------------*/
/*-                             INTERRUPCIONES                               -*/
/*----------------------------------------------------------------------------*/
#INT_RDA
void RDA_isr() {  
  // Caracter recibido por puerto serie (Bluetooth) 
  char tmp = getc();
  if (tmp != '\r' && tmp != '\n')
    Recibido = tmp;
}

/*----------------------------------------------------------------------------*/
/*-                          Programa Principal                              -*/
/*----------------------------------------------------------------------------*/
void main() {
  setup_oscillator(OSC_1MHz);

  // Configuración del CPP para el servo de la direccion. El no trucado.
  setup_timer_2(T2_DIV_BY_16, PERIODO_TIMER2, 4);
  setup_ccp1(CCP_PWM);

  // Modulacion PWM para los servos.
  // Usaríamos el timer 0 para medir el ancho de pulso.
  setup_timer_0(RTCC_INTERNAL | RTCC_DIV_1);
   
  //Iniciamos comunicación UART HC-05 -> PIC
  enable_interrupts(INT_RDA);
  enable_interrupts(GLOBAL);
  setup_uart(9600);

  // Enciende led de encendido
  output_high(PIN_LED_ENCENDIDO);

  // Bucle principal del programa (funcionamiento por interrupción).
  while(true) {
    switch (Recibido) {
      // Dirección: Hacia delante
      case 'w':
        CCP_1_LOW = 15;
        // CCP_2_LOW = 32;
        break;
      
      // Dirección: Hacia atrás
      case 's':
        CCP_1_LOW = 32;
        // CCP_2_LOW = 15;
        break;

      // Dirección: Izquierda
      case 'a': 
        CCP_1_LOW = 23;
        //CCP_2_LOW = 32;
        break;
      
      // Dirección: Derecha
      case 'd':
        CCP_1_LOW = 32;
        //CCP_2_LOW = 23;
        break;
      
      // Si no se pulsa nada... Poner el servo de giro a 0º.
      case 'p':
      default:
        CCP_1_LOW = 23;
        // CCP_2_LOW = 23;
        break;
    } 
  }
}
