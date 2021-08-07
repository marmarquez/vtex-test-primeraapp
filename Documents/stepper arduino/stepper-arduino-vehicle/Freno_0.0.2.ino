
 
/*
 * Este programa controla la frenada de un vehiculo desde un segundo puesto de conduccion. El control de la frenada se realiza mediante un pedal en el puesto de conduccion  que  gobierna un potenciometro 
 */

 //INCLUDES

// ENTRADAS DIGITALES

 const int btnFrenoIzda = 25;  // para frenar solo en la izda
 const int btnFrenoDcha = 27;  // idem dcha
 const int btnBloqueoFreno = 29;  // freno esacionamiento.
 const int btnDesbloqueFreno = 31; 
 const int  inversor; // el inversor de marcha no pertenece al sistema de frenada, pero queremos que se desbloquee el freno de estacionamiento cuando se de marcha atras. Tiene posicion de marcha adelante, atras y neutra.Puede ser una entrada analogica (miniJoystick ) o dos digitales ( atras y adelante). Por ahora lo escribo como si fuera una sola entrada digital.

  //con interrupción
 const int encoder1 = 4;
 const int encoder2 =5;
  
// ENTRADAS ANALOGICAS
  // de sensores
const int sensorPosicionFrenoPrimario = A0; // No lo llamo pedal pq a  lo mejor se conecta diresctaente al cilindro maestro de freno directamente por motivos de seguridad.
const int sensorPosicionPedalFreno secundario =A1;

   // de ajuste
const int potBalanceoFrenada =A3; // para que frene igual a los dos lados
    
const int potAjusteMinFrenada = A4;  // para que cuando se suelte el pedal secundario el freno primario este suelto y empiece a actuar nada más pisar el pedal secundario. Es un ajuste de error de cero. 
const int potAjusteFuerzaFrenada =A5; // Para que el freno primario responda mas o menos al pedal secundario. Es un ajuste de pendiente de una recta. si la frenada deseada es "y" y depende del pedal que es "x"  y= a + bx. Este pot ajusta b y el anterior ajusta a. 
const int potAjusteKp = A6;
const int potAjusteKi = A7;
const int potAjusteHisteresis = A8; // La histeresis ayuda a estabilizar un controlador PI.
// SALIDAS DIGITALES
const int  pulsePin= 47;
const int directionPin = 49;
const int driverEnable = 51;
// Seguramente haya más salidas para señales visuales (LEDS).

//SALIDAS PWM 
const int ledR = 10;// para controlar led RGB que ayuda a depurar y a dar mensajes al operador
const int ledG = 12;// idem
const int ledB = 11;// idem
const int buzzer = 3; //0 señal acustica para dar avisos al operador

// VARIABLES DEL PROGRAMA  // En principio no es una buena practica declarar todas las variable como globales, pero yo soy un programador muy malo. Tomate las libertades que creas convenientes para creitcar o rectificar.
float consignaFrenada =0;  // Normalmente me gusta referirme a las cantidades manejo con unidades reales, preferiblemente con unidaades del sistema Internacional, o unidades de uso extendido en la Industria. Ayuda a mantener los pies en el suelo y simplifica mandar informacion al operador en un HMI ( Human Machine Interface) si le pones una pantalla o algo así. En este caso, no se que unidad usar, angulo deseado de giro del motor de paso, carrera del cilindro maestro de frenada ( aquí en España se le llama curiosamente bomba de freno), o aceleración desedada en g's. Ya lo veremos. Normalmente prefiero referirme a la manifestación física final, que en nuestro caso puede ser la aceleración, pero eso puede provocar que el operador perciba la frenada de una manera distinta a la que está acostumbrado. Cuando hago esto en vez de llamarle consigna de frenada a la variable, la llamo, consignaAceleracion o consignaCarreraCilindroMaestro. Ya veremos.
float posicionCilindroFreno = 0; // Calculado con un pot que va al cilindroComo decía no hago los calculos ni la logica del programa con el valor devuelto por el pot. Primero lo convierto a unidades con sentido Fisico, por ejemplo centimetros. Solo usaría el valor bruto del pot si necesitase desesperadamente arañar unos microsegundos. En cierto modo es una capa de abstracción del hardware y por tanto ayuda en caso de rediseño del sistema.
float anguloGiroMotor = 0;// Calculado con el encoder.
float aceleración= 0;  //calculado con el acelerómetro.
float Kp = 1;  // constante proporcional del controlador PI del freno.
float Ki = 0.1; //  constante Integral del controlador PI del freno.
float histeresisFrenada = 0;  // Esto es un truco para mejorar la estabilidad de un controlador PI.
boolean  fallo = false; // Se puede usar para proceder en caso de que el sistema detecte un fallo por discrepancia entre sensores correlacionados. No  es necesario para las primeras versiones. Se puede declara int para diferenciar distintos niveles de alarma. Tambien se pueden declarar mas alarmas.
// seran necesarias más variables si queremos usar el acelerometro. No tienen porque ser globales.
 
void setup() {
  // put your setup code here, to run once:
Serial.begin(230400); // Inicializamos puerto serie para depurar. No eligo esos baudios por nada en particular salvo por ser una velocidad relativamente alta que no impida al controlador responder en tiempo real mientras se depura.
}

void loop() {


}

  
