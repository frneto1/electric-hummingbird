#define LED 5

// L298N
#define IN1 26
#define IN2 27
#define ENA 14
#define IN3 33
#define IN4 32
#define ENB 25

// Botões
#define BOTAO1 18
#define BOTAO2 19
#define BOTAO3 21

// PWM
#define MOTOR_FREQ 30000
#define MOTOR_RES 8

#define LED_FREQ 5000
#define LED_RES 8

void setup() {
  // LED
  pinMode(LED, OUTPUT);
  ledcAttach(LED, LED_FREQ, LED_RES);

  // Botões
  pinMode(BOTAO1, INPUT);
  pinMode(BOTAO2, INPUT);
  pinMode(BOTAO3, INPUT);

  // Motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcAttach(ENA, MOTOR_FREQ, MOTOR_RES);
  ledcAttach(ENB, MOTOR_FREQ, MOTOR_RES);

  pararMotor();
}

void loop() {

  if (digitalRead(BOTAO1) == HIGH) {
    executarModo(100, 300); // lento
  }
  else if (digitalRead(BOTAO2) == HIGH) {
    executarModo(120, 200); // médio
  }
  else if (digitalRead(BOTAO3) == HIGH) {
    executarModo(140, 120); // rápido
  }
  else {
    pararMotor();
    ledcWrite(LED, 0);
  }
}

// ============================
// FUNÇÕES
// ============================

void executarModo(int velocidade, int tempoBatimento) {
  moverMotor(velocidade);
  batimentoSuave(tempoBatimento);
}

void moverMotor(int velocidade) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  ledcWrite(ENA, velocidade);
  ledcWrite(ENB, velocidade);
}

void pararMotor() {
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);
}

// LED
void batimentoSuave(int tempo) {

  // subida rápida
  for (int i = 0; i < 255; i += 5) {
    ledcWrite(LED, i);
    delay(tempo / 50);
  }

  // descida lenta
  for (int i = 255; i > 0; i -= 3) {
    ledcWrite(LED, i);
    delay(tempo / 40);
  }

  // pausa
  delay(tempo);
}
