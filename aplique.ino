int led = 2;
int pulsador = 4;



//PULSACION
boolean estado_pulsador;
boolean corta;
boolean larga;

//temporizacion para pulsadores

unsigned long inicio_pulsacion = 0;
unsigned long t_pulsado = 0;



void setup() {
	pinMode(led, OUTPUT);
	pinMode(pulsador, INPUT);


	Serial.begin(115200);
}

void loop() {
	//leo el estado de las entradas
	estado_pulsador = digitalRead(pulsador);

	if (estado_pulsador == HIGH && inicio_pulsacion == 0) {
		inicio_pulsacion = millis();//inicializo el tiempo e impido que vuelva a funcionara hasta T_actual valga cero,


	}
	//calculo de la duraccion de la pulsación (T_pulsado)inicio_pulsacion
	if (estado_pulsador == LOW && inicio_pulsacion != 0) {

		t_pulsado = millis() - inicio_pulsacion;
		inicio_pulsacion = 0;
		Serial.println(t_pulsado/10);
	}
}