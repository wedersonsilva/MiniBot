/**************************************
 *        MINIBOT GLOVE V2.0          *
 *       (Mini - 10 x 10 cm)          *
 *                                    *
 *  Um robô controlado por uma luva   *
 *   github.com/wedersonsilva/lcfs    *
 *                                    *             
 * Autor: Wederson Silva (Sep 2018)   *
 **************************************/

/* INCLUSAO DE BIBLIOTECAS */
#include <VirtualWire.h>          // Necessaria para o uso do par RF 433Mz

/*  DEFINICAO DOS PINOS   */
const int PWM_A = 3;              // Pino de PWM do Motor A
const int PWM_B = 11;             // Pino de PWM do Motor B
int IN1 = 4;                      // Bit que define direcao do MOTOR A
int IN2 = 5;                      // Bit que define direcao do MOTOR A 
int IN3 = 6;                      // Bit que define direcao do MOTOR B
int IN4 = 7;                      // Bit que define direcao do MOTOR B

/*  DEFINICAO DE VARIAVEIS E VALORES  */
int VELOC_MAX = 60;               // Controle de velocidade dos motores 0 - 255
int FLAG = 0;                     // FLAG que auxilia na funcao PROCURA
byte message[VW_MAX_MESSAGE_LEN];    // Armazena as mensagens recebidas
byte msgLength = VW_MAX_MESSAGE_LEN; // Armazena o tamanho das mensagens

/*  DEFINICAO DE FUNCOES  */
void FRENTE();                    // Funcao que movimente robo para FRENTE
void TRAS();                      // Funcao que movimente robo para TRAS
void ESQUERDA();                  // Funcao que movimente robo para ESQUERDA
void DIREITA();                   // Funcao que movimente robo para DIREITA
void PARA();                      // Funcao que PARA o robo

/*  BLOCO DE CONFIGURACOES  */
void setup() {                    
  Serial.begin(9600);             // Necessario para PRINTAR MENSAGENS
  vw_set_rx_pin(8);               // Pino de dados do receptor
  vw_setup(2000);                 // Bits por segundo
  vw_rx_start();                  // Inicializa o receptor
  
  delay(600);                     // Durante 0.6 segundos

  pinMode(IN1, OUTPUT);           // Define de IN1 ate IN4 como pinos de saida
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(PWM_A, OUTPUT);         // Define os pinos de PWM dos motores A e B
  pinMode(PWM_B, OUTPUT);  
}

void FRENTE()                     // Funcao que movimente robo para FRENTE
{
  digitalWrite(IN1, LOW);         // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Serial.println("FRENTE");       // Mensagem para debugar o codigo
}

void TRAS()                       // Funcao que movimente robo para TRAS
{
  digitalWrite(IN1, HIGH);        // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("TRAS");         // Mensagem para debugar o codigo
}

void DIREITA()                    // Funcao que movimente robo para ESQUERDA
{
  digitalWrite(IN1, HIGH);        // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Serial.println("DIREITA");    // Mensagem para debugar o codigo
}

void ESQUERDA()                   // Funcao que movimente robo para DIREITA
{
  digitalWrite(IN1, LOW);         // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("ESQUERDA");   // Mensagem para debugar o codigo
}

void PARA()                       // Funcao que PARA o robo
{
  digitalWrite(IN1, LOW);         // De IN1 ate IN4 codigo para MOVIMENTAR O ROBO
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //Serial.println("PARA");       // Mensagem para debugar o codigo
}

void loop() {

  uint8_t message[VW_MAX_MESSAGE_LEN];    
  uint8_t msgLength = VW_MAX_MESSAGE_LEN; 
  vw_wait_rx();
    
  if (vw_get_message(message, &msgLength)) // Non-blocking
  {                                    
    for (int i = 0; i < msgLength; i++)
    {                        
      message[i] = message[i] - '0';      
    }
      if ((message[0] > 1 && message[2] < 4) && (message[3] < 4 && message[4] < 5)){
        DIREITA();
      }
      else if ((message[0] < 2 && message[2] > 3) && (message[3] < 4 && message[4] < 5)){
        FRENTE();
      }
      else if ((message[0] < 2 && message[2] < 4) && (message[3] > 3 && message[4] < 5)){
        TRAS();
      }
      else if ((message[0] < 2 && message[2] < 4) && (message[3] < 4 && message[4] > 4)){
        ESQUERDA();
      }
      else {
        PARA();     
      }
   }
       
  analogWrite(PWM_A, VELOC_MAX);
  analogWrite(PWM_B, VELOC_MAX);     
}
