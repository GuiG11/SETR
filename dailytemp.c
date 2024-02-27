#include "stdio.h"
#include "stdlib.h"

void dtInit(int vect[24]) {
    for (int i = 0; i < 24; i++) {
        vect[i] = 0;
    }
}

void dtAdd(int vect[24], int temp) {
    for (int i = 0; i < 24; i++) {
        if (vect[i] == 0) {
            vect[i] = temp;
            break;
        }
    }
}

void dtStat(int vect[24], int *max, int *min, int *avg) {
    int sum = 0;
    *max = vect[0];
    *min = vect[0];

    for (int i = 0; i < 24; i++) {
        if (vect[i] != 0) {
            if (vect[i] > *max) {
                *max = vect[i];
            }
            if (vect[i] < *min) {
                *min = vect[i];
            }
            sum += vect[i]; 
        }
    }

    *avg = sum / 24;
} 

int main() {
    int vect[24];
    dtInit(vect);
    
    for (int i = 0; i < 24; i++) {
        int temp;
        printf("Insert temperature value at %d:00 o'clock: \n",i);
        scanf("%d",&temp);

        if (temp < -50 || temp > 50) {
            printf("Invalid temperature value. Please insert a value between -50 and 50: \n");
            scanf("%d",&temp);
            dtAdd(vect,temp);
        } else {
            dtAdd(vect,temp);
        }

        printf("%d:00 : %dºC\n",i,vect[i]);
    }
    

    int max, min, avg;
    dtStat(vect,&max,&min,&avg);

    printf("Maximum temperature: %d\n", max);
    printf("Minimum temperature: %d\n", min);
    printf("Average temperature: %d\n", avg);
    
    return 0;
}
