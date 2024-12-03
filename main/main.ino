#include <Servo.h>

// Define o número de servos
const int numServos = 6;
// Cria um array de servos
Servo servos[numServos];
// Define os pinos dos servos
int servoPins[numServos] = {8, 9, 10, 11, 12, 13};

// Define os pontos
float pointsX[4] = {10.0,15.0,20.0,15.0};
float pointsY[4] = {15.0,15.0,18.0,15.0};
float pointsZ[4] = {10.0,15.0,13.0,15.0};
int points_num = 4;
// Define o intervalo entre ponto
int interval = 3000;
// Função cinemática que recebe coordenadas (x, y, z) e retorna 5 ângulos
void calculateKinematics(float x, float y, float z, float angles[5]) {
    // Implementação da cinemática inversa
    float L1 = 12.0; // Comprimento do primeiro segmento
    float L2 = 15.0; // Comprimento do segundo segmento

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
    angles[3] = 90; // Ângulo pulso
    angles[4] = 90; // Ângulo garra
}

void setup() {
  Serial.begin(115200);
    // Inicializa os servos
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(servoPins[i]);
        servos[i].write(90);
    }

}

void loop() {
    float angles[5];
    for(int i = 0; i < points_num; i++) {
        calculateKinematics(pointsX[i], pointsY[i], pointsZ[i], angles);
        Serial.println("-------------------");
        for (int j = 0; j < numServos; j++) {
          Serial.println(angles[j]);
            servos[j].write(angles[j]);
        }
        delay(interval);
    }
}