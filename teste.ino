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

  pinMode(LED, OUTPUT);

  pinMode(BOTAO1, INPUT_PULLUP);
  pinMode(BOTAO2, INPUT_PULLUP);
  pinMode(BOTAO3, INPUT_PULLUP);

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
    executarModo(110, 300);
  }
  else if (digitalRead(BOTAO2) == LOW) {
    Serial.println("Modo 2");
    executarModo(135, 200);
  }
  else if (digitalRead(BOTAO3) == LOW) {
    Serial.println("Modo 3");
    executarModo(160, 120);
  }
  else {
    pararMotor();
    batimentoLento(); // ❤️ LED bate devagar sem motor
  }
}

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

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);
}

void pararMotor() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// ❤️ Batimento normal (com motor)
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

// 💙 Batimento lento (sem motor)
void batimentoLento() {

  for (int i = 0; i < 255; i += 3) {
    analogWrite(LED, i);
    delay(20); // subida mais lenta
  }

  for (int i = 255; i > 0; i -= 2) {
    analogWrite(LED, i);
    delay(25); // descida mais suave
  }

  delay(400); // pausa maior
}
