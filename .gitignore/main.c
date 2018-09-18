#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 32000000 // FOSC
#include "flex_lcd.h"
#include<stdio.h>//STANDAR I/O



void main(void) {
   //Variables
    int adc;
    float voltaje;
    float adc1;
    float voltaje2;
    float temperatura;
    unsigned char buffer1 [16];
    
    //Oscilador Fosc=32MHZ
    OSCFRQbits.HFFRQ=0b110;
    
    //Puertos
    ANSELD=0; //Puertos D como digital
    ANSELE=0; //Puertos C como digital
    
    ANSELAbits.ANSA5=1; //RA5 como analogico
    TRISAbits.TRISA5=1; //RA5 como entrada
    ANSELAbits.ANSA4=1;
    TRISAbits.TRISA4=1;
    
    
    //convertidor analogico a digital
    ADCON0bits.ADON=1; //ADC ON
    ADCON0bits.ADCONT=0;//OPERACION NORMAL
    ADCON0bits.ADCS=1; //CLOCK SOURSE-FCR
    ADCON0bits.ADFRM=1; //Justificacion derecha
    ADREFbits.ADNREF=0; //Vref- ----- Vss
    ADREFbits.ADPREF=0b00; //Vref+ ----- VDD
    
    
    //*****************LCD
    Lcd_Init();// inicializa la LCD
    Lcd_Cmd(LCD_CLEAR); //LIMPIA LA LCD
    Lcd_Cmd(LCD_CURSOR_OFF);// APAGA EL CURSOR
    Lcd_Cmd(LCD_BLINK_CURSOR_ON);// PARPADEA EL CURSOE
    __delay_ms(100);
    
    //Ciclo infinito
    while (1){
    ADPCH=0b000101;
    __delay_ms(100);
    ADCON0bits.ADGO=1; //Inicia la convercion
    while (ADCON0bits.ADGO==1); //Espera 
    adc=ADRESH; //Me guarda el resultado
    adc=adc<<8; //Me guarda el resultado
    adc=adc+ADRESL; //Me guarda el resultado
    //adc=(ADRESH<<8) ADRESL;
    voltaje=adc*3.3/1023.0; //Conversion de voltaje
    sprintf(buffer1, "adc_%04d", adc);
    Lcd_Out2(1,1,buffer1);
    sprintf(buffer1, "volt=%0.2f", voltaje);
    Lcd_Out2(2,1,buffer1);
    __delay_ms(1000);
 
    
    ADPCH=0b000100;
    __delay_ms(100);
    ADCON0bits.ADGO=1; //Inicia la convercion
    while (ADCON0bits.ADGO==1); //Espera 
    adc1=ADRESH; //Me guarda el resultado
    adc1=adc1<<8; //Me guarda el resultado
    adc1=adc1+ADRESL; //Me guarda el resultado
    //adc=(ADRESH<<8) ADRESL
    //Temperatura
    temperatura=(voltaje2*100.00);
    sprintf(buffer1,"Temp %04.2f",temperatura);
     Lcd_Out2(2, 1, buffer1);            //escribimos en el renglon uno espaco 1 la que contiene buffer1
        __delay_ms(300);
        
    }
    return;
}
