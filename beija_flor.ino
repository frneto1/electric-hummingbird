#define LED 5

// L298N
#define IN1 8
#define IN2 7
#define ENA 9

#define IN3 6
#define IN4 4
#define ENB 10

// Botões
#define BOTAO1 2
#define BOTAO2 3
#define BOTAO3 12

void setup() {
  Serial.begin(9600);

  // LED
  pinMode(LED, OUTPUT);

  // Botões (AGORA CORRETO)
  pinMode(BOTAO1, INPUT_PULLUP);
  pinMode(BOTAO2, INPUT_PULLUP);
  pinMode(BOTAO3, INPUT_PULLUP);

  // Motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pararMotor();
}

void loop() {

  if (digitalRead(BOTAO1) == LOW) {
    Serial.println("Modo 1");
    executarModo(90, 300); // lento
  }
  else if (digitalRead(BOTAO2) == LOW) {
    Serial.println("Modo 2");
    executarModo(115, 200); // médio
  }
  else if (digitalRead(BOTAO3) == LOW) {
    Serial.println("Modo 3");
    executarModo(140, 120); // rápido
  }
  else {
    pararMotor();
    analogWrite(LED, 0);
  }
}

// ============================

void executarModo(int velocidade, int tempoBatimento) {
  moverMotor(velocidade);
  batimentoSuave(tempoBatimento);
}

void moverMotor(int velocidade) {
  // Motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Motor B
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void pararMotor() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// LED
void batimentoSuave(int tempo) {

  for (int i = 0; i < 255; i += 5) {
    analogWrite(LED, i);
    delay(tempo / 50);
  }

  for (int i = 255; i > 0; i -= 3) {
    analogWrite(LED, i);
    delay(tempo / 40);
  }

  delay(tempo);
}
