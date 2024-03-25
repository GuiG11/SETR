#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sensor.h"
#include "unity.h"

void readAllData()
{
    FILE *file;
    int temp, humidity, CO2;
    int lastTemp, lastHumidity, lastCO2;

    // Abre o arquivo para leitura
    file = fopen("values.csv", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Lê os valores até EOF
    while (fscanf(file, "%d, %d, %d", &temp, &humidity, &CO2) == 3) {
        lastTemp = temp;
        lastHumidity = humidity;
        lastCO2 = CO2;
    }
    
    fclose(file);

    printf("Real-time values:\n");
    printf("Temperature: %d, Humidity: %d, CO2: %d\n", lastTemp, lastHumidity, lastCO2);
}

void readOneValue(char choice)
{
    FILE *file;
    int temp, humidity, CO2;
    int lastValue;

    // Abre o arquivo para leitura
    file = fopen("values.csv", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Lê os valores do tipo especificado até EOF
    while (fscanf(file, "%d, %d, %d", &temp, &humidity, &CO2) == 3) {
        switch (choice) {
            case 'T':
                lastValue = temp;
                break;
            case 'H':
                lastValue = humidity;
                break;
            case 'C':
                lastValue = CO2;
                break;
            default:
                printf("Invalid value type.\n");
                fclose(file);
                return;
        }
    }

    fclose(file);

    printf("Real-time %c value: %d\n", choice, lastValue);
}

void returnLastSamples()
{
    FILE *file;
    char c;
    Data values[MAX_DATA];

    // Abre o arquivo para leitura
    file = fopen("values.csv", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Conta o número total de amostras
    int totalSamples = 0;
    int temp, humidity, CO2;
    while (fscanf(file, "%d, %d, %d", &temp, &humidity, &CO2) == 3) {
        totalSamples++;
    }

    // Calcula a posição inicial para ler as últimas 20 amostras
    int InitPos = totalSamples - MAX_SAMPLES;
    if (InitPos < 0) {
        InitPos = 0; // Se houver menos de 20 amostras, começa do início
    }

    // Retrocede a posição do arquivo para o início das últimas 20 amostras
    rewind(file);

    // Avança até a posição inicial
    for (int i = 0; i < InitPos; i++) {
        fscanf(file, "%*d, %*d, %*d"); // Ignora os valores das amostras
    }

    // Lê as últimas 20 amostras
    int counter = 0;
    while (counter < MAX_SAMPLES && fscanf(file, "%d, %d, %d", &values[counter].temp, &values[counter].humidity, &values[counter].CO2) == 3) {
        counter++;
    }

    fclose(file);

    // Exibe as últimas amostras lidas
    printf("Last 20 samples:\n");
    for (int i = counter-1; i >= 0; i--) {
        printf("Sample %d: Temperature = %d, Humidity = %d, CO2 = %d\n", counter-i,
               values[i].temp, values[i].humidity, values[i].CO2);
    }
}

void resetHistory()
{
    FILE *file;

    // Abre o arquivo para escrita, o que irá truncá-lo (esvaziar)
    file = fopen("values.csv", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Fecha o arquivo após truncá-lo
    fclose(file);

    printf("History reset successfully.\n");
}

void randomFill()
{
    FILE *file;

    // Abre o arquivo para escrita
    file = fopen("values.csv", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Inicializa a geração de números aleatórios
    srand(time(NULL));

    // Escreve as leituras no arquivo
    for (int i = 0; i < MAX_DATA-1; i++) {
        // Gera valores aleatórios para temperatura, humidade e CO2
        int temp = rand() % (60 - (-50) + 1) + (-50);
        int humidity = rand() % (100 - 0 + 1);
        int CO2 = rand() % (20000 - 400 + 1) + 400;

        // Escreve os valores no arquivo
        fprintf(file, "%d, %d, %d\n", temp, humidity, CO2);
    }

    // Fecha o arquivo após escrever os valores
    fclose(file);
}

void generateTestData() {
    FILE *file;

    // Open file for writing
    file = fopen("values.csv", "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write test data
    for (int i = 0; i < MAX_DATA; i++) {
        // Generate PREDICTABLE sensor values
        int temp = i % 60 - 50; // Temperature cycles from -50 to 59
        int humidity = (i * 2) % 101; // Humidity cycles from 0 to 100
        int CO2 = (i * 500) % 19501 + 400; // CO2 cycles from 400 to 20000

        // Write values on file
        fprintf(file, "%d, %d, %d\n", temp, humidity, CO2);
    }

    // Close file
    fclose(file);
}
