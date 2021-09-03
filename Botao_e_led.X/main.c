/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 24000000UL //informa a frequ�ncia do clock utilizado
#include <util/delay.h>
#include "avr/eeprom.h"
#include <stdbool.h>
#define DEBOUNCE_TIME 25 // define o tempo de debouncing
#define TIME_INPUT_TIME 300 //tempo para esperar depois de apertar o bot�o
#define EE_DX_WRT_WORD(addr,v)   EEdolock( EEwrite(uint16_t, addr, v); ) //define criado pelo MCC
/*
 C�digo que faz o AVR128DA48 ligar ou desligar o led a cada vez que se aperta o bot�o. 
 A ideia era que adicionar na EEPROM a quantidade de vezes que o bot�o foi acionado.
 No entanto, isso ainda n�o deu certo.
 C�digos comentados s�o outras maneiras de fazer o que j� foi feito ou s�o tentativas que ainda n�o deram certo.
*/
unsigned char button_state() { // Fun��o que verifica se o bot�o est� ou n�o ativado
    //Bitset(PORTC, 0x06);
    int a = PORTC.IN; //Faz com que a vari�vel a seja igual ao estado l�gico das portas C.
    a = a - 0b10000000; //verficia��o se o bot�o est� ou n�o ativado
    if (a < 0) {
        //if ((PORTC.IN == 0b00000011)||(PORTC.IN == 0b01000011)){
        _delay_ms(DEBOUNCE_TIME); //Processo de debouncing
        if (a < 0) {
            //if ((PORTC.IN == 0b00000011)||(PORTC.IN == 0b01000011)){
            _delay_ms(DEBOUNCE_TIME); //Processo de debuncing
            return 1; //informar que o bot�o foi apertado

        }
    }
    return 0; //informar que nada aconteceu
}

int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize(); //Criado pelo mcc

    /* Replace with your application code */
    while (1){
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_24M_gc); //escolhendo 
    //frequ�ncia do clock
   /*do{
        
    }while(NVMCTRL.STATUS = 0x02);
    eeLock(0);*/
    PORTC.PIN7CTRL = 0b00001000; //Ativando fun��o pull-up para uso do bot�o
    PORTC.DIR = 0b01000000; //Pino PC6 como output e o pino PC7 como input
    PORTC.OUT &= 0x00; //Acende o LED
    float i = 0;
   /* do{
        
    }while(NVMCTRL.STATUS = 0x02);
    eeLock(1);
    out $1E,r0; */
  /*  while (NVMCTRL.STATUS & (NVMCTRL_EEBUSY_bm | NVMCTRL_FBUSY_bm))
		;
    _PROTECTED_WRITE(NVMCTRL.CTRLA, 0x13); 
    
    *(uint8_t *)(0x1400U) = 0x03;
    
    _PROTECTED_WRITE(NVMCTRL.CTRLA, 0x00); */
    
    
    
    while (1) { //Gera um looping infinito

        if (button_state()) { //Chama a fun��o que ir� verificar se o bot�o est�
            //apertado
            i++;
            PORTC.OUTTGL = 0b01000000; //Fun��o toggle: altera a situa��o do LED
            //write_B_eeprom();
            // eeprom_update_float(i, );
            do {

            } while (button_state()); //Espera o bot�o parar de ser apertado
        }

    }
    }
}
/**
    End of File
*/