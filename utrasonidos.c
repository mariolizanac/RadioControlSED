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
#USE standard_io(b) // Para los ultrasonidos

/*----------------------------------------------------------------------------*/
/*-                             Constantes                                   -*/
/*----------------------------------------------------------------------------*/
#define PIN_LED_ENCENDIDO   PIN_A1
#define PERIODO_TIMER2      255      // Equivale a 18.4 ms (aprox.) 
#define trig                PIN_B0
#define echo                PIN_B1
int16 distancia = 10;
int16 tiempo;

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

#INT_TIMER1
void parada_obligada(){
  set_timer1(53036);
  //Se envia un pulso de 10us por los ultrasonidos
  output_high(trig);
  delay_us(10);
  output_low(trig);  
}

#INT_TIMER0
void calcula_distancia(){
  //Se mide el tiempo que tarda en volver el pulso de ultrasonidos
  set_timer0(0);
  while(input(echo)){
  }
  tiempo = get_timer0();
  distancia = (tiempo)/(58e-06);
}  

/*----------------------------------------------------------------------------*/
/*-                          Programa Principal                              -*/
/*----------------------------------------------------------------------------*/
void main() {
  setup_oscillator(OSC_1MHz);

  setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
  setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
  // Configuración del CPP para el servo de la direccion. El no trucado.
  setup_timer_2(T2_DIV_BY_16, PERIODO_TIMER2, 4);
  setup_ccp1(CCP_PWM);

   
  //Iniciamos comunicación UART HC-05 -> PIC
  enable_interrupts(INT_RDA);
  enable_interrupts(INT_TIMER0);
  enable_interrupts(INT_TIMER1);
  enable_interrupts(GLOBAL);
  setup_uart(9600);

  // Enciende led de encendido
  output_high(PIN_LED_ENCENDIDO);

  // Bucle principal del programa (funcionamiento por interrupción).
  while(true){
    if (distancia < 5  && Recibido == 'w'){
       CCP_1_LOW = 23;
       //CCP_2_LOW = 23;
    }
    else{
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
}
