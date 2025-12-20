// Biblioteca padrão para controle de servomotores
#include <Servo.h>

// ============================
// Declaração dos servos
// ============================

// Servo responsável pela rotação da base do braço
Servo servoBase;

// Servo do ombro (movimento vertical inicial)
Servo servoOmbro;

// Servo do cotovelo (alcance do braço)
Servo servoCotovelo;

// Servo da garra (abrir e fechar)
Servo servoGarra;

// ============================
// Posições iniciais dos servos
// ============================

// Ângulo inicial da base
int posBase = 90;

// Ângulo inicial do ombro
int posOmbro = 90;

// Ângulo inicial do cotovelo
int posCotovelo = 90;

// Ângulo inicial da garra
int posGarra = 90;

// ============================
// Pinos do motor do rolo compressor
// (usando ponte H L298N)
// ============================

int IN1 = 10;  // Controle de direção
int IN2 = 11;  // Controle de direção
int ENA = 12;  // Controle de velocidade (PWM)

// ============================
// Função setup()
// Executada apenas uma vez
// ============================

void setup() {

  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Associa cada servo ao seu respectivo pino
  servoBase.attach(3);
  servoOmbro.attach(5);
  servoCotovelo.attach(6);
  servoGarra.attach(9);

  // Define os pinos do motor como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Move os servos para a posição inicial
  servoBase.write(posBase);
  servoOmbro.write(posOmbro);
  servoCotovelo.write(posCotovelo);
  servoGarra.write(posGarra);

  // Mensagem inicial no Monitor Serial
  Serial.println("Sistema do braço robótico iniciado.");
  Serial.println("Use o teclado para controlar os movimentos.");
}

// ============================
// Função loop()
// Executada continuamente
// ============================

void loop() {

  // Verifica se há dados disponíveis na serial
  if (Serial.available() > 0) {

    // Lê o caractere digitado
    char comando = Serial.read();

    // Estrutura de decisão para cada comando
    switch (comando) {

      // ===== Base =====
      case 'q': posBase += 5; break; // Gira para a direita
      case 'a': posBase -= 5; break; // Gira para a esquerda

      // ===== Ombro =====
      case 'w': posOmbro += 5; break; // Sobe
      case 's': posOmbro -= 5; break; // Desce

      // ===== Cotovelo =====
      case 'e': posCotovelo += 5; break;
      case 'd': posCotovelo -= 5; break;

      // ===== Garra =====
      case 'r': posGarra += 5; break; // Abre
      case 'f': posGarra -= 5; break; // Fecha

      // ===== Rolo compressor =====
      case 't':  // Liga o rolo
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, 200); // Velocidade do motor
        break;

      case 'g':  // Para o rolo
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        break;
    }

    // ============================
    // Limita os ângulos dos servos
    // Evita danos mecânicos
    // ============================

    posBase = constrain(posBase, 0, 180);
    posOmbro = constrain(posOmbro, 0, 180);
    posCotovelo = constrain(posCotovelo, 0, 180);
    posGarra = constrain(posGarra, 0, 180);

    // ============================
    // Atualiza os servos
    // ============================

    servoBase.write(posBase);
    servoOmbro.write(posOmbro);
    servoCotovelo.write(posCotovelo);
    servoGarra.write(posGarra);
  }
}
