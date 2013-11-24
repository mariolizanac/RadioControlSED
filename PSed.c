/**********************************************************************
  Proyecto SED:4 Fantasticos   Special Guest:Vicente
  
  Comunicación Bluetooth Ordenador-automovil mediante PIC
  
  Miembros 4 Fantasticos:Borja,Benito,Mario,Pablo
  
  *********************************************************************/
  

//Primera toma de contacto con el proyecto. Proyecto_SED  Versión 0.0000


//////////////////////////////////////////////////////////////////////////////
// INCLUDEs FUSES USEs ///////////////////////////////////////////////////////


#include <18f4520.h>  // No sé si usaremos este modelo u otro.
#FUSES NOWDT
#FUSES INTRC
#FUSES PUT
#FUSES NOPROTECT
#FUSES NOBROWNOUT
#FUSES NOLVP
#FUSES NOMCLR
#use delay(clock=4000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,UART1,ERRORS)  // Como dijisteis usaremos USART para comunicacion HC-05-PIC




//////////////////////////////////////////////////////////////////////////////
// VARIABLES CONSTANTES //////////////////////////////////////////////////////

#define pinServoTraccion x




//////////////////////////////////////////////////////////////////////////////
// VARIABLES RAM /////////////////////////////////////////////////////////////

int8 periodo_timer2=255;            //Se corresponde con 18,4ms aproximadamente de periodo.




///////////////////////////////////////////////////////////////////////////////
// INTERRUPCIONES /////////////////////////////////////////////////////////////

#INT_RDA
RDA_isr(){  

  int8 recibido;
  recibido=getc();                 //Recibe 87, 83, 65 o 68 si usamos las teclas w,s,a,d.
                                   //Aquí pondriamos las instrucciones para nuestro coche.


  switch (recibido){
    /*Hacia delante y atrás. Servo trucado*/
    case "87":                    //Adelante. Considero w.
    output_high(pinServoTraccion)
    delay_ms(2);                  //2.5 son +90º, como lo hemos trucado va hacia la delante siempre.
    output_low(pinServoTraccion);
    delay_ms(20);
    break;

    case "83":                    //Atrás. Considero s.
    output_high(pinServoTraccion)
    delay_ms(1);                  //0.5 son -90º, como lo hemos trucado va hacia la atrás siempre.
    output_low(pinServoTraccion);
    delay_ms(20);
    break;


    /*Hacia izquierda y derecha. Servo NO trucado. Uso del unico CCP del 18F4580*/
    case "65":                    //Izquierda. Considero a.
    CCP_1_LOW=15;                 //Gira a la izquierda.
    break;
    case "68":                    //Derecha. Considero d.
    CCP_1_LOW=32;                 //Gira a la derecha.
    break;
    default:
    CCP_1_LOW=23.5;               //Por defecto en medio.


  }
}




///////////////////////////////////////////////////////////////////////////////
// Programa Principal /////////////////////////////////////////////////////////

void main(){
  disable_interrupts(GLOBAL);

  setup_timer_2(T2_DIV_BY_16, periodo_timer2 ,4);     //Setup del CPP para el servo de la direccion. El NO trucado.
  setup_ccp1(CCP_PWM);
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);            //Usaríamos el tmr0 para medir el ancho de pulso... Modulacion PWM para los servos
  setup_uart(9600);                                   //Iniciamos comunicación UART HC-05 -> PIC


  eneable_interrupt(INT_RDA);
  eneable_interrupt(GLOBAL);

  while(true){}
}
      
      
   
   // Para mandar datos del pc al modulo bluetooth podemos usar UART LINK 2.0
   // Os dejo enlace de pagina http://www.vallecompras.com/msln/pdf/Manual_HC_05.pdf
   // También faltaría toda la parte de control de servos y bibliotecas adicionales
   // Es solo una primera plantilla para trabajar sobre ella
