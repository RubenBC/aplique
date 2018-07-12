/*mido el tiempor de pulsacion 1
si es menos de 500ms se activa  P1_corta y enciendo led verde
si es mas de 500 ms se activa P2_larga y apago led verde

En este programa se ha programado la impresion cada segundo con una funcion pulso.

*/

//fastled
#include <FastLED.h>
#define NUM_LEDS 95
#define DATA_PIN 6
int superior[] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,
					57,58,59,60,61,62,63,64,65,66,67,68};
CRGB leds[NUM_LEDS];


int pulsador1 = 4;



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



void setup() {
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

	pinMode(pulsador1, INPUT);

	Serial.begin(115200);

}

void loop() {
	//leo el estado de las entradas
	pul_1 = digitalRead(pulsador1);

	if (pul_1 == HIGH && T_inicio_pulsacion == 0) {
		T_inicio_pulsacion = millis(); //inicializo el tiempo e impido que vuelva a funcionara hasta T_actual valga cero,


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
	// PULSACION CORTA
	if (P1_corta == 1) {
		Serial.println("pulsacion corta");
		estado_luz = modo_luz++;
		if (estado_luz == 0) {
			apagar();
			Serial.println("enciendo superior");
			encenderSuperior();
		}
		if (estado_luz == 1) {
			apagar();
			Serial.println("enciendo rainbow");
			rainbow();
		}
		if (estado_luz == 2){
			apagar();
			Serial.println("enciendo todo");
			leer();
		}
		if (estado_luz == 3) {
			apagar();
			delay(50);
			Serial.println("enciendo todo");
			calida();
		}
		if (estado_luz == 4) {
			modo_luz = 0;
			apagar();
			delay(50);
			Serial.println("vuelvo a encender superior");
		}

		Serial.println(estado_luz);
		P1_corta = 0;
	}

	// PULSACION LARGA
	if (P1_larga == 1) {
			apagar();
		}

		P1_larga = 0;
	}


//fin loop

void encenderSuperior()
{
	for (byte i = 0; i < 38; i++)
	{
		FastLED.setBrightness(250);
		leds[superior[i]] = CRGB(250, 250, 140);
	}
	delay(50);
	FastLED.show();
}

void apagar() {

	for (byte i = 0; i < 95; i++)
	{
		FastLED.setBrightness(0);
		leds[i] = CRGB(0, 0, 0);
	}
	delay(50);
	FastLED.show();
}

void rainbow() {
	for (byte i = 0; i < 10; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(255, 0, 255);  // violeta

	}
	for (byte i = 10; i < 20; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(50, 0, 110); // morado

	}
	for (byte i = 20; i < 30; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(0, 0, 255); // azul

	}
	for (byte i = 30; i < 41; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(0, 255, 0); // verde
;
	}
	for (byte i = 41; i < 52; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(255, 255, 0); // amarillo

	}
	for (byte i = 52; i < 63; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(255, 127, 0); // naranja

	}
	for (byte i = 63; i < 73; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(255, 0, 0); // rojo

	}
	for (byte i = 73; i < 95; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(255, 255, 255); // blanco

	}
	delay(50);
	FastLED.show();

}

void leer() {
	for (byte i = 0; i < 95; i++)
	{
		FastLED.setBrightness(255);
		leds[i] = CRGB(255, 255, 255); // blanco
	}
	delay(50);
	FastLED.show();
}

void calida() {

	for (byte i = 0; i < 95; i++)
	{
		FastLED.setBrightness(250);
		leds[i] = CRGB(250, 250, 50);
	}
	delay(50);
	FastLED.show();
}
