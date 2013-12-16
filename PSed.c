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
#use rs232(baud=9600, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8) 

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
#define PIN_SERVO_TRACCION PIN_C3
#define PERIODO_TIMER2     255      // Equivale a 18.4 ms (aprox.)

#define LCD_COMANDO 0
#define LCD_BORRAR  1

/*----------------------------------------------------------------------------*/
/*-                             INTERRUPCIONES                               -*/
/*----------------------------------------------------------------------------*/
// CHECK: ¡¡Estamos usando delays dentro de una interrupción!!
#INT_RDA
void RDA_isr() {  
  int i;          // Variable de iteración
  char recibido;  // Caracter recibido por puerto serie (Bluetooth)
  
  // En caso de que haya dato un caracter en el buffer, lo leemos
  if (kbhit()) 
    recibido = getc();               
  // CHECK: ¿En caso contrario se debe seguir ejecutando la función?
  //        ¿Se podría dar el caso contrario?

  switch (recibido) {
    // Dirección: Hacia delante
    case 'w':
      output_high(PIN_SERVO_TRACCION);
      // Delay: 2.5 para +90º. Como está trucado va hacia la delante siempre.
      delay_ms(2);  
      output_low(PIN_SERVO_TRACCION);
      delay_ms(20);
      break;
    
    // Dirección: Hacia atrás
    case 's':
      output_high(PIN_SERVO_TRACCION);
      // Delay: 0.5 para -90º. Como está trucado va hacia la atrás siempre.
      delay_ms(1);
      output_low(PIN_SERVO_TRACCION);
      delay_ms(20);
    break;

    // Dirección: Izquierda
    case 'a': 
      // Mantenemos el giro durante cierto tiempo.
      for (i = 0; i <= 20; i++) {
        output_high(PIN_C5);
        delay_ms(1);
        output_low(PIN_C5);
        delay_ms(20);
      }
      
      // Vuelta a cero del servo de dirección
      output_high(PIN_C5);
      delay_us(1500);  
      output_low(PIN_C5);
      delay_ms(20);
    break;
    
    // Dirección: Derecha
    case 'd':
      // Mantenemos el giro durante cierto tiempo.
      for (i = 0; i <= 20; i++) {
        output_high(PIN_C5);
        delay_ms(2);
        output_low(PIN_C5);
        delay_ms(20);
      }
      
      // Vuelta a cero del servo de dirección
      output_high(PIN_C5);
      delay_us(1500);       
      output_low(PIN_C5);
      delay_ms(20);  
    break;
    
    // Si no se pulsa nada... Poner el servo de giro a 0º.
    default:
      output_low(PIN_C5);       
      output_low(PIN_SERVO_TRACCION);
      break;
  } 
}

/*----------------------------------------------------------------------------*/
/*-                          Programa Principal                              -*/
/*----------------------------------------------------------------------------*/
void main() {
  disable_interrupts(GLOBAL);

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

  // Bucle principal del programa (funcionamiento por interrupción).
  while(true) ;
}
