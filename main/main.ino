#include <Servo.h>

// Define o número de servos
const int numServos = 6;
// Cria um array de servos
Servo servos[numServos];
// Define os pinos dos servos
int servoPins[numServos] = {2, 3, 4, 5, 6, 7};

// Função cinemática que recebe coordenadas (x, y, z) e retorna 5 ângulos
void calculateKinematics(float x, float y, float z, float angles[5]) {
    // Implementação da cinemática inversa
    float L1 = 10.0; // Comprimento do primeiro segmento
    float L2 = 10.0; // Comprimento do segundo segmento

    // Ângulo da base
    angles[0] = atan2(y, x) * 180 / PI;

    // Distância do plano base ao ponto (x, y)
    float r = sqrt(x*x + y*y);

    // Ângulo do ombro
    float D = (r*r + z*z - L1*L1 - L2*L2) / (2 * L1 * L2);
    angles[2] = atan2(sqrt(1 - D*D), D) * 180 / PI;

    // Ângulo do cotovelo
    float theta1 = atan2(z, r);
    float theta2 = atan2(L2 * sin(angles[2] * PI / 180), L1 + L2 * cos(angles[2] * PI / 180));
    angles[1] = (theta1 + theta2) * 180 / PI;

    // Ângulo do pulso e garra (ajustar conforme necessário)
    angles[3] = 0; // Ângulo pulso
    angles[4] = 0; // Ângulo garra
}

void setup() {
    // Inicializa os servos
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(servoPins[i]);
    }
}

void loop() {
    // Exemplo de uso da função cinemática
    float angles[5];
    calculateKinematics(10.0, 10.0, 10.0, angles);
    for (int i = 0; i < 5; i++) {
        Serial.println(angles[i]);
    }
}