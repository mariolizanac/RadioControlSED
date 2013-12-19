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
#use delay(clock=32MHz)  // CHECK: Mejor usamos 8Mhz 
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
#define PIN_SERVO_TRACCION  PIN_B0
#define PIN_SERVO_DIRECCION PIN_B1
#define PIN_ENCENDIDO       PIN_A1
#define PERIODO_TIMER2      255      // Equivale a 18.4 ms (aprox.)

#define LCD_COMANDO 0
#define LCD_BORRAR  1

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
  byte i;
  
  //disable_interrupts(GLOBAL);

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
  output_high(PIN_ENCENDIDO);

  // Bucle principal del programa (funcionamiento por interrupción).
  while(true) {
    switch (Recibido) {
      // Parada
      case 'p':
        output_low(PIN_SERVO_TRACCION);
        output_low(PIN_SERVO_DIRECCION);
        break;
    
      // Dirección: Hacia delante
      case 'w':
        output_high(PIN_SERVO_TRACCION);
        // Delay: 2.5 para +90º. Como está trucado va hacia la delante siempre.
        delay_ms(1000);  
        output_low(PIN_SERVO_TRACCION);
        delay_ms(2000);
        break;
      
      // Dirección: Hacia atrás
      case 's':
        output_high(PIN_SERVO_TRACCION);
        // Delay: 0.5 para -90º. Como está trucado va hacia la atrás siempre.
        delay_ms(1000);
        output_low(PIN_SERVO_TRACCION);
        delay_ms(2000);
        break;

      // Dirección: Izquierda
      case 'a': 
        // Mantenemos el giro durante cierto tiempo.
        for (i = 0; i <= 20; i++) {
          output_high(PIN_SERVO_DIRECCION);
          delay_ms(1000);
          output_low(PIN_SERVO_DIRECCION);
          delay_ms(2000);
        }
        
        // Vuelta a cero del servo de dirección
        output_high(PIN_SERVO_DIRECCION);
        delay_us(1500);  
        output_low(PIN_SERVO_DIRECCION);
        delay_ms(2000);
        break;
      
      // Dirección: Derecha
      case 'd':
        // Mantenemos el giro durante cierto tiempo.
        for (i = 0; i <= 20; i++) {
          output_high(PIN_SERVO_DIRECCION);
          delay_ms(2000);
          output_low(PIN_SERVO_DIRECCION);
          delay_ms(20000);
        }
        
        // Vuelta a cero del servo de dirección
        output_high(PIN_SERVO_DIRECCION);
        delay_us(1500);       
        output_low(PIN_SERVO_DIRECCION);
        delay_ms(2000);  
        break;
      
      // Si no se pulsa nada... Poner el servo de giro a 0º.
      default:
        output_low(PIN_SERVO_DIRECCION);       
        output_low(PIN_SERVO_TRACCION);
        break;
    } 
  
  }
}
