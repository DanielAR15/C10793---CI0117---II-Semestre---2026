#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100000000
#define NUM_HILOS 4

volatile char acumulador_global = 0.0;
char estado_hilos[NUM_HILOS] = {0};
double *vector;

void* calcular_suma_vectorial(void* rank) {
    
    long id_hilo = (long)rank;
    long tam_bloque = N / NUM_HILOS;
    long inicio = id_hilo * tam_bloque;
    long fin = inicio + tam_bloque;

    int i;
    for (i = inicio; i < fin; i++) {
        acumulador_global = acumulador_global + vector[i];
    }

    estado_hilos[id_hilo] = 1;

    return NULL;
}

int main(int argc, char* argv[]) {
    vector = (double*) malloc(N * sizeof(double));

    int i;
    for (i = 0; i < N; i++) {
        vector[i] = 1.0;
    }

    pthread_t hilos[NUM_HILOS];
    long id_hilo;

    for (id_hilo = 0; id_hilo < NUM_HILOS; id_hilo++) {
        pthread_create(&hilos[id_hilo], NULL, calcular_suma_vectorial, (void*) id_hilo);
    }

    for (i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("El resultado de la suma es: %d\n", acumulador_global);

    for (i = 0; i < NUM_HILOS; i++) {
        printf("estado_hilos[%d] = %d\n", i, estado_hilos[i]);
    }

    free(vector);

    return 0;
}
