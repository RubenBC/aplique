/*mido el tiempor de pulsacion 1
si es menos de 500ms se activa  P1_corta y enciendo led verde
si es mas de 500 ms se activa P2_larga y apago led verde

En este programa se ha programado la impresion cada segundo con una funcion pulso.

*/

#include <power_mgt.h>
#include <platforms.h>
#include <pixeltypes.h>
#include <pixelset.h>
#include <noise.h>
#include <lib8tion.h>
#include <led_sysdefs.h>
#include <hsv2rgb.h>
#include <fastspi_types.h>
#include <fastspi_ref.h>
#include <fastspi_nop.h>
#include <fastspi_dma.h>
#include <fastspi_bitbang.h>
#include <fastspi.h>
#include <fastpin.h>
#include <fastled_progmem.h>
#include <fastled_delay.h>
#include <fastled_config.h>
#include <dmx.h>
#include <cpp_compat.h>
#include <controller.h>
#include <colorutils.h>
#include <colorpalettes.h>
#include <color.h>
#include <chipsets.h>
#include <bitswap.h>
#include <FastLED.h>
#define NUM_LEDS 95
int pulsador1 = 4;
int ledverde = 2;




//PULSACION
boolean pul_1;
boolean P1_corta;
boolean P1_larga;

//temporizacion para pulsadores
unsigned long T_inicio_pulsacion = 0;
unsigned long T_pulsado = 0;

// Estados de luz
byte modo_luz = 0;
byte estado_luz;
boolean encendido = false;



void setup() {
	pinMode(ledverde, OUTPUT);
	digitalWrite(ledverde, 1);
	pinMode(pulsador1, INPUT);
	Serial.begin(115200);
}

void loop() {
	//leo el estado de las entradas
	pul_1 = digitalRead(pulsador1);

	if (pul_1 == HIGH && T_inicio_pulsacion == 0) {
		T_inicio_pulsacion = millis();//inicializo el tiempo e impido que vuelva a funcionara hasta T_actual valga cero,


	}

	//calculo de la duraccion de la pulsación (T_pulsado)T_inicio_pulsacion
	if (pul_1 == LOW && T_inicio_pulsacion != 0) {

		T_pulsado = millis() - T_inicio_pulsacion;
		T_inicio_pulsacion = 0;
	}

	if (T_pulsado>20 && T_pulsado<500) {
		P1_corta = 1;
		T_pulsado = 0;

	}

	if (T_pulsado >= 500) {
		P1_larga = 1;
		T_pulsado = 0;

	}

	if (P1_corta == 1) {
		Serial.println("pulsacion corta");
		// Si encendido es false lo pongo a true y enciendo  el led
		if (encendido == false) {
			encendido = true;
			digitalWrite(ledverde,0);
		}
		// si encendido es true lo pongo a false y apago el led
		else { encendido = false; 
		digitalWrite(ledverde, 1);
		}
		P1_corta = 0;
	}

	if (P1_larga == 1) {
		Serial.println("larga");
		estado_luz = modo_luz++;
		Serial.println(estado_luz);

		P1_larga = 0;
	}


}//fin de programa