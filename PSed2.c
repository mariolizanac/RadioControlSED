//////////////////////////////////////////////////////////////////////////////
// INCLUDEs FUSES USEs ///////////////////////////////////////////////////////


#include <18f4520.h>  // No sÃ© si usaremos este modelo u otro.
#FUSES NOWDT
#FUSES INTRC
#FUSES PUT
#FUSES NOPROTECT
#FUSES NOBROWNOUT
#FUSES NOLVP
#FUSES NOMCLR
#use delay(clock=1000000)  // Mejor usamos 1Mhz 
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)  // Como dijisteis usaremos USART para comunicacion HC-05-PIC
#include "LCDeasy.c"



//////////////////////////////////////////////////////////////////////////////
// VARIABLES CONSTANTES //////////////////////////////////////////////////////

#define pinServoDerecha PIN_C1    //pin del ccp2
#define pinServoIzquierda PIN_C2  //pin del ccp1




//////////////////////////////////////////////////////////////////////////////
// VARIABLES RAM /////////////////////////////////////////////////////////////

int8 periodo_timer2=255;            //Se corresponde con 18,4ms aproximadamente de periodo.

#INT_RDA
void RDA_isr(){  

   
  char recibido; // Definimos tipo char. No tipo int8
  if(kbhit()) recibido=getc();    //Si tenemos datos en el buffer kbhit nos da un true entonces asignamos a recibidos el tipo char del teclado             

      
   if(recibido=='w'){                    //Adelante. Considero w.
    CCP_1_LOW=32;
    CCP_2_LOW=15;
   }
    if(recibido=='s'){             //AtrÃ¡s. Considero s.
    CCP_1_LOW=15;
    CCP_2_LOW=32;
    }

    // Ahora hacia derecha e izquierda
    if(recibido=='a'){ 
    CCP_1_LOW=15;
    CCP_2_LOW=15;                //Simplemente lo he hecho con delays y pulsos en alta o en baja.
    }
    if(recibido=='d'){
    CCP_1_LOW=32;
    CCP_2_LOW=32;        
    }//Gira a la derecha.
    else{
    CCP_1_LOW=23;
    CCP_2_LOW=23;
    }
       
    //CCP_1_LOW=23.5;     
    }//Por defecto en medio.





void main()
{
   
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_timer_2(T2_DIV_BY_16, periodo_timer2 ,4);   //Carga el periodo (registro PR2 del CCP) y activa TMR2
                                             //El post-scaler (4 en este caso) podría usarse para
                                             //la generación de interrupciones del TMR2 (en este ejemplo no se usa) 

//El módulo CCP1 se congigura en el modo PWM con salida de señal por RC2/CCP:

   setup_ccp1(CCP_PWM);         //Configura el modo PWM para el CCP1
   setup_ccp2(CCP_PWM);         //Configura el modo PWM para el CCP2 
    
  setup_uart(9600);
  // Cogi la libreria de lcdeasy simplemente para tener una especie de mensaje de entrada  (opcional)
  lcd_init();                    
   lcd_send_byte(0, 1); //Borra LCD

   printf("Instrucciones del coche: \n\r -Pulsando 'w' va hacia delante 
           \n\r -Pulsando 's' va para detras \n\r-Pulsando 'd' va hacia la derecha \n\r-Pulsando 'a' va hacia la izquierda \n\r Por favor, No lo coja si ha bebido\n\r");




   while(TRUE){}
}
