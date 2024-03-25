#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sensor.h"
#include "unity.h"

void readAllData()
{
    FILE *file;
    char c;
    int i = 0;
    Data values[MAX_DATA];

    // Abre o arquivo para leitura
    file = fopen("values.csv", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Ignora os caracteres até encontrar o marcador de início
    while ((c = fgetc(file)) != '#') {
        if (c == EOF) {
            printf("Invalid file format.\n");
            fclose(file);
            return;
        }
    }

    // Lê os valores até encontrar o marcador de fim
    while (fscanf(file, "%d, %d, %d", &values[i].temp, &values[i].humidity, &values[i].CO2) == 3) {
        i++;
        if (i >= MAX_DATA) {
            printf("Maximum value limit reached.\n");
            break;
        }
    }

    fclose(file);

    // Exibe os valores lidos
    printf("Reading values:\n");
    for (int j = 0; j < i; j++) {
        printf("Temperature: %d, Humidity: %d, CO2: %d\n", values[j].temp, values[j].humidity, values[j].CO2);
    }
}

void readOneValue(char choice)
{
    FILE *file;
    char c;
    int temp, humidity, CO2;

    // Determina qual valor será lido com base no tipo especificado
    switch (choice) {
        case 'T':
            printf("Reading temperature values:\n");
            break;
        case 'H':
            printf("Reading humidity values:\n");
            break;
        case 'C':
            printf("Reading CO2 values:\n");
            break;
        default:
            printf("Invalid value type.\n");
            return;
    }

    // Abre o arquivo para leitura
    file = fopen("values.csv", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Ignora os caracteres até encontrar o marcador de início
    while ((c = fgetc(file)) != '#') {
        if (c == EOF) {
            printf("Invalid file format.\n");
            fclose(file);
            return;
        }
    }

    // Lê os valores do tipo especificado
    while (fscanf(file, "%d, %d, %d", &temp, &humidity, &CO2) == 3) {
        // Dependendo do tipo especificado, exibe o valor correspondente
        switch (choice) {
            case 'T':
                printf("Temperature: %d\n", temp);
                break;
            case 'H':
                printf("Humidity: %d\n", humidity);
                break;
            case 'C':
                printf("CO2: %d\n", CO2);
                break;
        }

        // Lê o caractere de nova linha após o valor
        fgetc(file);

        // Verifica se encontrou o marcador de fim
        if ((c = fgetc(file)) == '!') {
            break;
        } else {
            // Move o cursor de volta para o início do próximo valor
            fseek(file, -1, SEEK_CUR);
        }
    }

    fclose(file);
}

void returnLastSamples()
{
    FILE *file;
    char c;
    Data values[MAX_SAMPLES];

    // Abre o arquivo para leitura
    file = fopen("values.csv", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Ignora os caracteres até encontrar o marcador de início
    while ((c = fgetc(file)) != '#') {
        if (c == EOF) {
            printf("Invalid file format.\n");
            fclose(file);
            return;
        }
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

    // Ignora os caracteres até encontrar o marcador de início novamente
    while ((c = fgetc(file)) != '#') {
        if (c == EOF) {
            printf("Invalid file format.\n");
            fclose(file);
            return;
        }
    }

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
    fprintf(file, "#\n"); // Marca de início
    for (int i = 0; i < MAX_DATA-1; i++) {
        // Gera valores aleatórios para temperatura, humidade e CO2
        int temp = rand() % (60 - (-50) + 1) + (-50);
        int humidity = rand() % (100 - 0 + 1);
        int CO2 = rand() % (20000 - 400 + 1) + 400;

        // Escreve os valores no arquivo
        fprintf(file, "%d, %d, %d\n", temp, humidity, CO2);
    }
    fprintf(file, "!\n"); // Marca de fim

    // Fecha o arquivo após escrever os valores
    fclose(file);
}