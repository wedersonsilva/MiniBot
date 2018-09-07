/****************************************************
 *        MINIBOT V3.0 (Mini - 10 x 10 cm)          *
 *                                                  *
 *  Um robô para Batalha Sumô autônomo ou Bluetooth *
 *                                                  *
 * Autor: Wederson Silva (Nov 2017)                 *
 ***************************************************/

/*  DEFINICAO DOS PINOS   */
const int SL1 = A1;               // Sensor de linha da FRENTE
const int SL2 = A2;               // Sensor de linha de TRAS
const int TRIG = 11;              // TRIG Ultrasson
const int ECHO = 12;              // ECHO Ultrasson
const int PWM_A = 3;              // Pino de PWM do Motor A
const int PWM_B = 10;             // Pino de PWM do Motor B
int IN1 = 4;                      // Bit que define direcao do MOTOR A
int IN2 = 5;                      // Bit que define direcao do MOTOR A 
int IN3 = 6;                      // Bit que define direcao do MOTOR B
int IN4 = 7;                      // Bit que define direcao do MOTOR B

/*  DEFINICAO DE VARIAVEIS E VALORES  */
int VALOR_SL1 = 0;                // Captura o valor do sensor de linha da frente
int VALOR_SL2 = 0;                // Captura o valor do sensor de linha de tras
unsigned long TEMPO_PULSO;        // Tempo do pulso do ultrasson
unsigned long DISTANCIA;          // Distancia calculada
int LIMIAR = 100;                 // Limiar de valor para considerar linha branca
int VELOC_MAX = 100;               // Controle de velocidade dos motores 0 - 255
int FLAG = 0;                     // FLAG que auxilia na funcao PROCURA
int BLUE_FLAG = 0;                // FLAG que define se usará ou não o Bluetooth
char DIRECAO = 'A';               // DIRECAO RECEBIDA POR BLUETOOTH

/*  DEFINICAO DE FUNCOES  */
void LER_SL();                    // Funcao para LER SENSOR DE LINHA
void LER_SOM();                   // Funcao para LER SENSOR ULTRASSONICO
void FRENTE();                    // Funcao que movimente robo para FRENTE
void TRAS();                      // Funcao que movimente robo para TRAS
void ESQUERDA();                  // Funcao que movimente robo para ESQUERDA
void DIREITA();                   // Funcao que movimente robo para DIREITA
void PROCURAR();                  // Funcao que PROCURA O ADVERSARIO
void ESCAPAR();                   // Funcao para ESCAPAR DA LINHA BRANCA
void BLUETOOTH();                 // Funcao de controle BLUETOOTH

/*  BLOCO DE CONFIGURACOES  */
void setup() {                    
  Serial.begin(9600);             // Necessario para PRINTAR MENSAGENS
  delay(2000);                    // ESPERA DE 3 SEGUNDOS (5 SEG NO TOTAL)

  FRENTE();                       // GIRA PARA A ESQUERDA
  delay(600);                     // Durante 0.6 segundos

  pinMode(IN1, OUTPUT);           // Define de IN1 ate IN4 como pinos de saida
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PWM_A, OUTPUT);         // Define os pinos de PWM dos motores A e B
  pinMode(PWM_B, OUTPUT);
  
  pinMode(TRIG, OUTPUT);          // Define TRIG como SAIDA
  pinMode(ECHO, INPUT);           // Define ECHO como ENTRADA
}

void LER_SL()                     // Funcao para LER SENSOR DE LINHA
{
  VALOR_SL1 = analogRead(SL1);      // LER SENSOR DE LINHA FRENTE
  VALOR_SL2 = analogRead(SL2);      // LER SENSOR DE LINHA TRAS

  Serial.print("SL1 = ");
  Serial.print(VALOR_SL1);
  Serial.print(" "); 
  Serial.print("SL2 = ");
  Serial.println(VALOR_SL2);
}

void FRENTE()                     // Funcao que movimente robo para FRENTE
{
  digitalWrite(IN1, LOW);         // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void TRAS()                       // Funcao que movimente robo para TRAS
{
  digitalWrite(IN1, HIGH);        // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void ESQUERDA()                   // Funcao que movimente robo para ESQUERDA
{
  digitalWrite(IN1, HIGH);        // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void DIREITA()                    // Funcao que movimente robo para DIREITA
{
  digitalWrite(IN1, LOW);         // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void PROCURAR()                   // Funcao que PROCURA O ADVERSARIO
{     
  FLAG = FLAG + 1;                // FLAG para auxiliar a funcao de PROCURAR
  
  if(FLAG <= 15){                  
    DIREITA();                    // Girar para a DIREITA
  }
  else if((FLAG > 15) && (FLAG <= 22)){ 
    FRENTE();                     // Ir para FRENTE
  }
  else if((FLAG > 22) && (FLAG <= 37)){ 
    ESQUERDA();                   // Girar para a ESQUERDA
  }
  else if ((FLAG > 37) && (FLAG <= 44)){
    FRENTE();                     // Ir para FRENTE
  }
  else{
    //FLAG = 0;
    FLAG = random(45);             // Use RANDOM quando FLAG > 6
  }
}

void ESCAPAR()                    // Funcao para ESCAPAR DA LINHA BRANCA
{ 
  //Serial.print(" ESCAPAR ");
  FLAG = 0;
  
  if((VALOR_SL1 > LIMIAR) && (VALOR_SL2 < LIMIAR)){
    TRAS();                         // Ir para TRAS  
    delay(250);
  }
  else if((VALOR_SL2 > LIMIAR) && (VALOR_SL1 < LIMIAR)){
    FRENTE();
    delay(250);
  }  
  else{
    ESQUERDA();
    delay(100);                   
    FLAG = 0;                       // ZERA A FLAG para quando o ROBO PROCURAR O ADVERSARIO
  }
  
}

void LER_SOM()                    // Funcao para LER SENSOR ULTRASSONICO
{ 
  digitalWrite(TRIG, LOW);        // Desliga o TRIG
  delayMicroseconds(5);           // Espera por 0.005 SEGUNDOS
  digitalWrite(TRIG, HIGH);       // Liga o TRIG
  delayMicroseconds(10);          // Espera por 0.010 SEGUNDOS
  digitalWrite(TRIG, LOW);        // Desliga o TRIG
  
  TEMPO_PULSO = pulseIn(ECHO, HIGH);    // CALCULA O TEMPO DO PULSO DO ULTRASSOM
  DISTANCIA = (TEMPO_PULSO / 2) / 29.1; // CALCULA A DISTANCIA em CENTIMETROS      

  Serial.print("Distância = ");
  Serial.print(DISTANCIA);
  Serial.println(" cm");  
}  

void BLUETOOTH(){
  BLUE_FLAG = 1;

  if(DIRECAO == 'F'){
    FRENTE();
  }
  else if(DIRECAO == 'B'){
    TRAS();  
  }
  else if(DIRECAO == 'R'){
    DIREITA();  
  }
  else if(DIRECAO == 'L'){
    ESQUERDA();  
  }
  else if(DIRECAO == 'A'){
    TRAS();    
  }
}

void loop() {

  LER_SL();                       // LER SENSOR DE LINHA
  LER_SOM();                      // LER SENSOR ULTRASSON  

  if((DIRECAO != 'A') || (BLUE_FLAG == 1))
  {
    BLUETOOTH();
  }
  

  analogWrite(PWM_A, VELOC_MAX);
  analogWrite(PWM_B, VELOC_MAX);  
  
  if((VALOR_SL1 > LIMIAR) || (VALOR_SL2 > LIMIAR))           
  {
    ESCAPAR();                    // FUGIR
  }  
  else if(DISTANCIA < 40){        // SE DISTANCIA < 30 CM
    FRENTE();                     // ATACAR
    Serial.println("FRENTE");
  }
  else if(DISTANCIA > 39){        // SE DISTANCIA > 29 CM
    PROCURAR();                   // PROCURAR ADVERSARIO
    Serial.println("PROCURAR");
  }       
}
