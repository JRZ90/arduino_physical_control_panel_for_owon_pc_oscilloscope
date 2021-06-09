
int A = 2;                       //Variable A a pin digital 2 (DT en modulo)
int B = 4;                      //Variable B a pin digital 4 (CLK en modulo)
int ANTERIOR = 50;             //Almacena valor anterior de la variable POSICION
volatile int POSICION = 50;   //Variable POSICION con valor inicial de 50 y definida
//                           //Como global al ser usada en loop e ISR (encoder)

const int PulsadorEnc = 12;                //Pin al cual se conecta el pulsador del encoder
int estado = 1;                           //Contador: variable que acumula el numero de pulsaciones
int estadoPulsadorEnc = 0;               //Variable que almacena el estado actual del pulsador
int estadoAnteriorPulsadorEnc = 0;      //Variable que almacena el estado anterior del pulsador
///

const int PulsadorUno = 7;
const int PulsadorDos = 6;
const int PulsadorTres = 8;

int estadoPulsadorUno = 0;
int estadoAnteriorPulsadorUno = 0;
int estadoPulsadorDos = 0;
int estadoAnteriorPulsadorDos = 0;
int estadoPulsadorTres = 0;
int estadoAnteriorPulsadorTres = 0;
///
int ledCh1 = 14;
int ledCh2 = 15;
int ledBaseTiempo = 16;

void setup() {
  pinMode(A, INPUT);                   //A como entrada
  pinMode(B, INPUT);                  //B como entrada
  pinMode(PulsadorEnc, INPUT);       //Inicializa el pin del pulsador como entrada
  Serial.begin(9600);               //Inicializa la comunicación Serie
  pinMode(16, OUTPUT);             //Declaramos el pin 16 como salida
  pinMode(15, OUTPUT);            //Declaramos el pin 15 como salida
  pinMode(14, OUTPUT);           //Declaramos el pin 14 como salida
  pinMode(12, INPUT);           //Declaramos el pin 12 como entrada
  pinMode(7, INPUT);           //Declaramos el pin 7 como entrada
  pinMode(6, INPUT);          //Declaramos el pin 6 como entrada
  pinMode(5, INPUT);         //Declaramos el pin 5 como entrada

  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, LOW);

  Serial.println("102");  //Imprime en monitor serial 102 indicando a python que esta listo

  attachInterrupt(digitalPinToInterrupt(A), encoder, LOW);  //Interrupcion sobre pin A con
  //                                                       //Funcion ISR encoder y modo LOW
  attachInterrupt(digitalPinToInterrupt(B), encoder, LOW);
}

void loop() {
  /////////////////////////////Encoder////////////////////////////////

  if (POSICION != ANTERIOR) {    //Si el valor de POSICION es distinto de ANTERIOR
    Serial.println(POSICION);   //Imprime valor de POSICION
    delay(50);
    POSICION = 50;
    ANTERIOR = POSICION ;    //Asigna a ANTERIOR el valor actualizado de POSICION
  }

  /////////////////////////////Pulsador encoder///////////////////////

  estadoPulsadorEnc = digitalRead(PulsadorEnc);          //Se lee y almacena el estado del pulsador
  if (estadoPulsadorEnc != estadoAnteriorPulsadorEnc) { //Se compara la variable estadoPulsadorEnc
    //                                                 //Con su valor anterior
    delay(200);
    estado = 1 + estado;                             //Pasó de un estado OFF a ON
    Serial.println(estado + 100);                   //Manda un código numerico a python para ejecutar
  }//                                              //la tarea asignada

  ///////////////---------Estados---------///////////////

  if (estado == 1) {                    //si el estado es 1
    delay(40);
    digitalWrite(ledCh1, HIGH);       //se enciende el led del canal 1
  }
  else {                            //si el estado es 0
    digitalWrite(ledCh1, LOW);     //se apaga el led
  }

  /////////////////////////////////////////////

  if (estado == 2) {
    delay(40);
    digitalWrite(ledCh2, HIGH);
  }
  else {
    digitalWrite(ledCh2, LOW);
  }

  /////////////////////////////////////////////

  if (estado == 3)  {
    delay(40);
    digitalWrite(ledBaseTiempo, HIGH);
  }
  else {
    digitalWrite(ledBaseTiempo, LOW);
  }

  if (estado > 3) {         //si estado es mayor que 3 reinicia la variable a 1
    (estado = 1);
  }

  //////////////////////////////////Pulsadores/////////////////////////////////////

  estadoPulsadorUno = digitalRead(PulsadorUno);             //Se lee y almacena el estado del pulsadorUno
  if (estadoPulsadorUno != estadoAnteriorPulsadorUno) {    //Se compara la variable estadoPulsadorUno
    //                                                    //con su valor anterior
    delay(100);
    Serial.println(1);                                  //Manda un código numerico a python para ejecutar
  }//                                                  //la tarea asignada

  estadoPulsadorDos = digitalRead(PulsadorDos);
  if (estadoPulsadorDos != estadoAnteriorPulsadorDos) {
    delay(100);
    Serial.println(2);
  }

  estadoPulsadorTres = digitalRead(PulsadorTres);
  if (estadoPulsadorTres != estadoAnteriorPulsadorTres) {
    delay(100);
    Serial.println(3);
  }

}

void encoder()  {
  static unsigned long ultimaInterrupcion = 0;            //Variable static con ultimo valor de
  //                                                     //Tiempo de interrupcion
  unsigned long tiempoInterrupcion = millis();          //Variable almacena valor de func. millis

  if (tiempoInterrupcion - ultimaInterrupcion > 5) {  //Rutina antirebote desestima
    //                                               //Pulsos menores a 5 mseg.
    if (digitalRead(B) == HIGH)  //Si B es HIGH, sentido horario
    {
      POSICION++ ;             //Incrementa POSICION en 1
    }
    else {                   //Si B es LOW, senti anti horario
      POSICION-- ;          //Decrementa POSICION en 1
    }

    POSICION = min(100, max(0, POSICION));      //Establece limite inferior de 0 y
    //                                         //Superior de 100 para POSICION
    ultimaInterrupcion = tiempoInterrupcion;  //Guarda valor actualizado del tiempo
  } //                                       //De la interrupcion en variable static
}
