#include <Servo.h>

// Define o número de servos
const int numServos = 6;
// Cria um array de servos
Servo servos[numServos];
// Define os pinos dos servos
int servoPins[numServos] = {2, 3, 4, 5, 6, 7};

void setup() {
    // Inicializa os servos
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(servoPins[i]);
    }
}

void loop() {
    // Move os servos
    for (int i = 0; i < numServos; i++) {
        servos[i].write(90);
        delay(1000);
        servos[i].write(0);
        delay(1000);
    }
}