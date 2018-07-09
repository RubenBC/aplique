/*mido el tiempor de pulsacion 1
si es menos de 500ms se activa  P1_corta y enciendo led verde
si es mas de 500 ms se activa P2_larga y apago led verde

En este programa se ha programado la impresion cada segundo con una funcion pulso.

*/

//fastled
#include <FastLED.h>
#define NUM_LEDS 95
#define DATA_PIN 6
int superior[] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,51,53,54,55,56,
					57,58,59,60,61,62,63,64,65,66,67,68};
CRGB leds[NUM_LEDS];


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
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

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
			encenderSuperior();
		}
		// si encendido es true lo pongo a false y apago el led
		else { encendido = false; 
		apagarSuperior();
		}
		P1_corta = 0;
	}

	if (P1_larga == 1) {
		Serial.println("larga");
		estado_luz = modo_luz++;
		Serial.println(estado_luz);

		P1_larga = 0;
	}


}//fin loop

void encenderSuperior()
{
	for (byte i = 0; i < 38; i++)
	{
		FastLED.setBrightness(250);
		leds[superior[i]] = CRGB(250, 250, 140);
	}
	FastLED.show();
	delay(10);
}

void apagarSuperior()
{
	for (byte i = 0; i < 38; i++)
	{
		FastLED.setBrightness(250);
		leds[superior[i]] = CRGB(0, 0, 0);
	}
	FastLED.show();
	delay(10);
}