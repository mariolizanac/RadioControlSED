/**********************************************************************
  Proyecto SED:4 Fantasticos   Special Guest:Vicente
  
  Comunicaci√≥n Bluetooth Ordenador-automovil mediante PIC
  
  Miembros 4 Fantasticos:Borja,Benito,Mario,Pablo
  
  *********************************************************************/
  

//Primera toma de contacto con el proyecto. Proyecto_SED  Versi√≥n 0.0000


//////////////////////////////////////////////////////////////////////////////
// INCLUDEs FUSES USEs ///////////////////////////////////////////////////////


#include <18f4520.h>  // No s√© si usaremos este modelo u otro.
#FUSES NOWDT
#FUSES INTRC
#FUSES PUT
#FUSES NOPROTECT
#FUSES NOBROWNOUT
#FUSES NOLVP
#FUSES NOMCLR
#use delay(clock=8000000)  // Mejor usamos 8Mhz 
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)  // Como dijisteis usaremos USART para comunicacion HC-05-PIC
#include "LCDeasy.c"




//////////////////////////////////////////////////////////////////////////////
// VARIABLES CONSTANTES //////////////////////////////////////////////////////

#define pinServoTraccion PIN_C3 //Asigno por ejemplo el PIN_C3 para la simulaciÛn en proteus




//////////////////////////////////////////////////////////////////////////////
// VARIABLES RAM /////////////////////////////////////////////////////////////

int8 periodo_timer2=255;            //Se corresponde con 18,4ms aproximadamente de periodo.




///////////////////////////////////////////////////////////////////////////////
// INTERRUPCIONES /////////////////////////////////////////////////////////////

#INT_RDA
void RDA_isr(){  

  char recibido; // Definimos tipo char. No tipo int8
  if(kbhit()) recibido=getc();    //Si tenemos datos en el buffer kbhit nos da un true entonces asignamos a recibidos el tipo char del teclado             

      
   if(recibido=='w'){                    //Adelante. Considero w.
    output_high(pinServoTraccion);
    delay_ms(2);                  //2.5 son +90¬∫, como lo hemos trucado va hacia la delante siempre.
    output_low(pinServoTraccion);
    delay_ms(20);
   }
    if(recibido=='s'){
                       //Atr√°s. Considero s.
    output_high(pinServoTraccion);
    delay_ms(1);                  //0.5 son -90¬∫, como lo hemos trucado va hacia la atr√°s siempre.
    output_low(pinServoTraccion);
    delay_ms(20);
    }


    // Ahora hacia derecha e izquierda
    if(recibido=='a'){ 
     output_high(PIN_C5);
    delay_ms(1);                  //ProbÈ con la versiÛn anterior con proteus y no va lo del ccp. Si alguno lo soluciona mejor
    output_low(PIN_C5);
    delay_ms(20);                     //Simplemente lo he hecho con delays y pulsos en alta o en baja.
    //CCP_1_LOW=14; 
   //Gira a la izquierda.
    }
    if(recibido=='d'){ 
       output_high(PIN_C5);
    delay_ms(2);                  //Igual que el anterior.
    output_low(PIN_C5);
    delay_ms(20);           //Derecha. Considero d.
    //CCP_1_LOW=31;    
    }//Gira a la derecha.
    else{
    output_low(PIN_C5);       //AquÌ tendrÌamos que poner que si no se pulsa nada que el servo de giro vuelva a 0∫
    output_low(pinServoTraccion);
    }
       
    //CCP_1_LOW=23.5;     
    }//Por defecto en medio.


 
  
  





///////////////////////////////////////////////////////////////////////////////
// Programa Principal /////////////////////////////////////////////////////////

void main(){
  disable_interrupts(GLOBAL);

  setup_timer_2(T2_DIV_BY_16, periodo_timer2 ,4);     //Setup del CPP para el servo de la direccion. El NO trucado.
  setup_ccp1(CCP_PWM);
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);            //Usar√≠amos el tmr0 para medir el ancho de pulso... Modulacion PWM para los servos
                                //Iniciamos comunicaci√≥n UART HC-05 -> PIC
  enable_interrupts(INT_RDA);
  enable_interrupts(GLOBAL);
  setup_uart(9600);
  // Cogi la libreria de lcdeasy simplemente para tener una especie de mensaje de entrada  (opcional)
  lcd_init();                    
   lcd_send_byte(0, 1); //Borra LCD

   printf("Instrucciones del coche: \n\r -Pulsando 'w' va hacia delante 
           \n\r -Pulsando 's' va para detras \n\r-Pulsando 'd' va hacia la derecha \n\r-Pulsando 'a' va hacia la izquierda \n\r Por favor, No lo coja si ha bebido\n\r");

  while(true){}
}
      
      //Podeis probar el codigo con el modelo de proteus que subi a Dropbox y usarlo para comprar el codigo que modifiqueis
   
   // Para mandar datos del pc al modulo bluetooth podemos usar UART LINK 2.0
   // Os dejo enlace de pagina http://www.vallecompras.com/msln/pdf/Manual_HC_05.pdf
   // Tambi√©n faltar√≠a toda la parte de control de servos y bibliotecas adicionales
   // Es solo una primera plantilla para trabajar sobre ella
