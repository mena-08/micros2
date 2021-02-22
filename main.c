/*
 * Titulo PRACTICA1_PEDRO_OMAR
 *
 * Created: 30/01/2021
 * Author : OMAR MENA; PEDRO GONZALEZ
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>				//Libreria general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
//#include <avr/interrupt.h>	 //Para poder manejar interrupciones

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER "LUGAR"
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
//*************************************************************************


int main(void)
{
	DDRA = 0;
	PORTA |= (15<<0);
	
	DDRB = 255;
	PORTB = 255;
    /* Codigo principal */
    while (1) 
    {
		uint8_t digito;
		digito = PINA;
		
		//if (cero==0){
		//	PORTB = 0b00000001;
		//}
		if (digito==0b00000001){
			_delay_ms(100);
			while(uno_en_bit(&PINA,0)){
				
			}
			_delay_ms(100);
			PORTB=0b11001111;
		}
		
		
		
		/* Las funciones de revisar bits pueden usarse como:
		   if(cero_en_bit(&PINA,2)) {}
		   o bien como:
		   while(cero_en_bit(&PINA,2)){}
		   entre otras opciones*/
    }
}




uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (*LUGAR&(1<<BIT));
}