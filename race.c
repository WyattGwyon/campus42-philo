//#include "./philo.h"
#define CORREDORES 5
#define ETAPAS 5
#define TIEMPO_MIN 100000
#define TIEMPO_MAX 2000000
void *correr(void *arg) {
    t_datos *datos = (t_datos *)arg;
    int id = datos->id;
    int *ganador = datos->ganador;
    pthread_mutex_t *mutex = datos->mutex;
    struct timeval inicio, fin;
    gettimeofday(&inicio, NULL);
    for (int i = 0; i < ETAPAS; i++) {
        int tiempo = TIEMPO_MIN + rand() % (TIEMPO_MAX - TIEMPO_MIN + 1);
        usleep(tiempo);
        printf("Corredor %d terminó la etapa %d\n", id, i + 1);
    }
    gettimeofday(&fin, NULL);
    long segundos = fin.tv_sec - inicio.tv_sec;
    long micros = fin.tv_usec - inicio.tv_usec;
    double tiempo_total = segundos + micros / 1e6;
    pthread_mutex_lock(mutex);
    if (*ganador == -1) {
        *ganador = id;
        printf(":tada: Corredor %d llegó primero en %.3f segundos!\n", id, tiempo_total);
    } else {
        printf("Corredor %d terminó en %.3f segundos\n", id, tiempo_total);
    }
    pthread_mutex_unlock(mutex);
    return NULL;
}
int main(void) {
    pthread_t hilos[CORREDORES];
    t_datos datos[CORREDORES];
    int ids[CORREDORES];
    int ganador = -1;
    pthread_mutex_t mutex_ganador = PTHREAD_MUTEX_INITIALIZER;
    srand(time(NULL));
    for (int i = 0; i < CORREDORES; i++) {
        datos[i].id = i + 1;
        datos[i].ganador = &ganador;
        datos[i].mutex = &mutex_ganador;
        if (pthread_create(&hilos[i], NULL, correr, &datos[i]) != 0) {
            perror("Error al crear hilo");
            return 1;
        }
    }
    for (int i = 0; i < CORREDORES; i++) {
        pthread_join(hilos[i], NULL);
    }
    printf(":white_check_mark: Carrera finalizada. Ganador: Corredor %d\n", ganador);
    pthread_mutex_destroy(&mutex_ganador);
    return 0;
}
