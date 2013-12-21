/******************************************************************************/
/**        Proyecto SED: 4 Fantasticos | Special Guest: Vicente              **/
/**                                                                          **/
/**       Comunicacionn Bluetooth Ordenador-Autovil mediante PIC            **/
/**                                                                          **/ 
/**         Miembros 4 Fantasticos: Borja, Benito, Mario, Pablo              **/
/**                        Copyright (C) 2013                                **/
/******************************************************************************/
#define VERSION 0.0.1
#include <18f4520.h>

/*----------------------------------------------------------------------------*/
/*-             Configuracion de modulos del microcontrolador                -*/
/*----------------------------------------------------------------------------*/
#device ADC=10
#use delay(clock=1MHz)  // Usaremos 1Mhz para el control de Servomotores 
#use rs232(baud=9600, uart1) //Activamos modulo UART
#use standard_io(a)
#use standard_io(b)

/*----------------------------------------------------------------------------*/
/*-                         Bits de configuracion                            -*/
/*----------------------------------------------------------------------------*/
#FUSES NOWDT        // Perro guardian desactivado
#FUSES INTRC        // Reloj interno del micro
#FUSES PUT          // Delay de inicio para asegurar estabilidad
#FUSES NOPROTECT    // Proteccion de codigo desactivada
#FUSES NOBROWNOUT   // Reinicio por caida de voltaje desactivado
#FUSES LVP          // Â¡NO CAMBIAR! Habilita la programacion en bajo voltaje

/*----------------------------------------------------------------------------*/
/*-                             Constantes                                   -*/
/*----------------------------------------------------------------------------*/
#define PIN_LED_ENCENDIDO   PIN_D1     //Led de control   
#define PERIODO_TIMER2      255      // Equivale a 18.4 ms (aprox.)
#define trig                PIN_B0
#define echo                PIN_B1

int16 CDER,CIZQ;
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
void pulso_ultrasonidos(){
  set_timer1(53035);
  //Se envia un pulso de 10us por los ultrasonidos
  output_high(trig);
  delay_us(10);
  output_low(trig);  
}

/*----------------------------------------------------------------------------*/
/*-                             Funciones de control                         -*/
/*----------------------------------------------------------------------------*/

void leer_infrarrojos(){

  set_adc_channel(0);
  delay_us(10);
  CDER = read_adc();
  set_adc_channel(1);
  delay_us(10);
  CIZQ = read_adc();
}

void Girar_Izquierda(){
  CCP_1_LOW = 32;
  CCP_2_LOW = 23;
}

void Girar_Derecha(){
  CCP_1_LOW = 23;
  CCP_2_LOW = 32;
}

void Mover_Adelante(){
  CCP_1_LOW = 32;
  CCP_2_LOW = 15;
}

void Mover_Atras(){
  CCP_1_LOW = 15;
  CCP_2_LOW = 32;
}

void Permanecer_Quieto(){
  CCP_1_LOW = 23;
  CCP_2_LOW = 23;
}

void seguidor(){

  leer_infrarrojos();
    
  if (CDER == CIZQ){
    Mover_Adelante();
  }
  else{
    if (CDER > CIZQ){
      Girar_Izquierda();
    }
    else{
      Girar_Derecha();
    }
  }
}

void seguidor_luz(){

  leer_infrarrojos();
    
  if (CDER == CIZQ){
    Mover_Adelante();
  }
  else{
    if (CDER > CIZQ){
      Girar_Derecha();
    }
    else{
      Girar_Izquierda();
    }
  }
}


/*----------------------------------------------------------------------------*/
/*-                          Programa Principal                              -*/
/*----------------------------------------------------------------------------*/
void main() {
  setup_oscillator(OSC_1MHz);  // Frecuencia interna de 1 Mhz para el control de servomotores
  
  //Configuracion de las interrupciones para el uso de ultrasonidos
  setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
  setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
  
  // Configuracion del CPP para el servo de la direccion. El no trucado.
  setup_timer_2(T2_DIV_BY_16, PERIODO_TIMER2, 4);
  setup_ccp1(CCP_PWM);
  setup_ccp2(CCP_PWM);
  //Configuración de la adquisición de luz
  setup_adc_ports(AN0_TO_AN1);
  setup_adc(adc_clock_div_2);   //comprobar segun el pic
  delay_us(10);
   
  //Iniciamos comunicacion UART HC-05 -> PIC
  enable_interrupts(INT_RDA);
  //enable_interrupts(INT_TIMER1);
  enable_interrupts(GLOBAL);
  setup_uart(9600);

  // Enciende led de encendido
  output_high(PIN_LED_ENCENDIDO);

  // Bucle principal del programa (funcionamiento por interrupcion externa).
  while(true) {
    /*while(!input(echo))                     
    {}
    set_timer0(0);                         
    while(input(echo))                     
    {}
    tiempo=get_timer0();
    distancia=(tiempo*10)/(58.0);
    */
    if (distancia < 5 && Recibido == 'w'){
      Permanecer_Quieto();
    }
    else{
      switch (Recibido) {
        // Direccion: Hacia delante
        case 'w':
          Mover_Adelante();
          break;
      
        // Direccion: Hacia atras
        case 's':
          Mover_Atras();
          break;

        // Direccion: Izquierda
        case 'a': 
          Girar_Izquierda();
          break;
      
        // Direccion: Derecha
        case 'd':
          Girar_Derecha();
          break;
        
        //Modo de funcionamiento seguidor de linea
        case 'l':
          seguidor();
          break;
      
        //Modo de funcionamiento seguidor de luz
        case 'o':
          seguidor_luz();
        break;
        // Si no se pulsa nada... Poner el servo de giro a 0º.
        case 'p':
        default:
          Permanecer_Quieto();
          break;
      } 
    }
  }
}
