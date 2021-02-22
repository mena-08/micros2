/*
 * Practica 1 
 *
 * Created: 30/01/2021
 * Author : Omar Mena Facio
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
//#include <avr/interrupt.h>	 //Para poder manejar interrupciones

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER "LUGAR"
//*************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
volatile uint8_t teclado[4][4] = {{1,2,3,10},
{4,5,6,11},
{7,8,9,12},
{14,0,15,13}};
uint8_t tecladoFuncion(volatile uint8_t *DDRT, volatile uint8_t *PORTT, volatile uint8_t *PINT);

//*************************


int main(void){
	
	DDRA = 0B00000000;
	PORTA = 0B11111111;
	
	DDRC = 0B11111111;
	PORTC = 0B00000000;
	uint8_t contador=97;
		
    /* Codigo principal */
    while (1) 
    {
		uint8_t lectura = tecladoFuncion(&DDRA,&PORTA,&PINA);
		
		if (lectura<10)
		{
			PORTC=lectura;
		}
		
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

uint8_t tecladoFuncion(volatile uint8_t *DDRT, volatile uint8_t *PORTT, volatile uint8_t *PINT) {
	//La funcion tecladoFuncion se quedará trabada hasta el momento en que se presione una tecla
	//Esta función regresa un valor del tipo uint8_t que tendrá que ser asignada a una variable
	//Ejemplo:

	//uint8_t tecla;
	//tecla = tecladoFuncion(&DDRA,&PORTA,&PINA);

	*DDRT = (1<<7)|(1<<6)|(1<<5)|(1<<4);		// definimos puerto para teclado
	
	while(1) {
		
		*PORTT = 0b11111111;
		
		for (uint8_t fila = 7; fila > 3; fila--) {
			
			*PORTT = ~(1<<fila);
			_delay_us(2);
			
			for (uint8_t col = 0; col < 4; col++) {
				
				if (cero_en_pin(PINT,col)) {
					_delay_ms(100);
					while(cero_en_pin(PINT,col)) {}
					_delay_ms(100);
					return teclado[7-fila][col];
				}
			}
		}
	}
}
