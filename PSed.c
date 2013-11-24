/**********************************************************************
  Proyecto SED:4 Fantasticos   Special Guest:Vicente
  
  Comunicación Bluetooth Ordenador-automovil mediante PIC
  
  Miembros 4 Fantasticos:Borja,Benito,Mario,Pablo
  
  *********************************************************************/
  

//Primera toma de contacto con el proyecto. Proyecto_SED  Versión 0.0000




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

#INT_RDA
RDA_isr()
{  int8 dat;
dat=getc();
//Aquí pondriamos las instrucciones para nuestro coche.
if (dat==''){
}
//Podriamos usar case y ver los posibles casos.Falta meter librerias de servo y funciones para estos.

void main()
{
// Activamos interrupciones del timer0
   
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1); //Usaríamos el tmr0 para medir el ancho de pulso... Modulacion PWM para los servos
   setup_uart(9600); //Iniciamos comunicación UART HC-05 -> PIC
   eneable_interrupt(INT_RDA);
   eneable_interrupt(GLOBAL);
   while(true){}
}
      
      
   
   // Para mandar datos del pc al modulo bluetooth podemos usar UART LINK 2.0
   // Os dejo enlace de pagina http://www.vallecompras.com/msln/pdf/Manual_HC_05.pdf
   // También faltaría toda la parte de control de servos y bibliotecas adicionales
   // Es solo una primera plantilla para trabajar sobre ella
