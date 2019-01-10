// Acionamento Solenoide e MP3 - Versao 1.0
// By Clederson T. Przybysz - clederson_p@yahoo.com.br
// expressoarduino.blogspot.com
// Criação: Março/2018

//Copyright Notes:
// O SOFTWARE É FORNECIDO "NO ESTADO EM QUE SE ENCONTRAM", SEM GARANTIA DE QUALQUER TIPO, EXPRESSA OU IMPLÍCITA, MAS NÃO SE LIMITANDO ÀS GARANTIAS DE COMERCIALIZAÇÃO.  
// EM NENHUMA CIRCUNSTÂNCIA, O AUTOR/TITULAR DE DIREITOS AUTORAIS SE RESPONSABILIZA POR QUALQUER RECLAMAÇÃO, DANOS OU OUTRA RESPONSABILIDADE, 
// SEJA EM AÇÃO DE CONTRATO, DELITO OU DE OUTRA FORMA, DECORRENDO DESTE SOFTWARE OU RELACIONADO AO SEU  USO.


//Pinos de Controle
#define pinSensor 2
#define pinSom 3
#define pinSino 4

//Intervalos de Tempo
#define intervalobatida 1900
#define minutoshora 6
#define delaySomMovimento 100

byte hora=0;
byte segundos=0;
byte minutos=0;
unsigned long TimeLoopSegundos;

void setup() {
  pinMode(pinSensor, INPUT);
  pinMode(pinSom, OUTPUT);
  pinMode(pinSino, OUTPUT);
  digitalWrite(pinSom, LOW);
  digitalWrite(pinSino, LOW);
  
  //Aguarda Modulo MP3 Iniciar
  delay(3000);
  BateVarias(2);
}

void loop() {
  if (millis()-TimeLoopSegundos>999) {
    TimeLoopSegundos = millis();
    segundos++;
    //Incrementa Minutos
    if (segundos==60) {
      segundos=0;
      minutos++;
    }
    //Toca Sino Hora
    if (minutos==minutoshora) {
      minutos=0;
      hora++;
      if (hora==25) hora=1;
      BateVarias(hora);
    }
    
  }
  //Se precionado botao toca uma vez
  byte val = digitalRead(pinSensor);
  if (val == 1) {
    BateSino();
    delay(1000);
  }
}



void BateVarias(byte batidas) {
  for (byte i = 0; i < batidas; i++) {
      BateSino();
      delay(intervalobatida);
    } 
}

void BateSino() {
  //Aciona MP3
  digitalWrite(pinSom, HIGH);
  delay(500);
  digitalWrite(pinSom, LOW);

  //Delay Som/Movimento
  delay(delaySomMovimento);
  
  //Aciona Solenoide
  digitalWrite(pinSino, HIGH);
  delay(500);
  digitalWrite(pinSino, LOW);
}
