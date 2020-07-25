#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t   threads[5];
int sum = 0;

void * adder(void * n) {
    printf("thread: %d\n", (int) n);
    for (int i = 0; i < 100000000; i++)
        sum += 1;
    printf("%d\n", sum);
    pthread_exit((void *) 0);
}

// Foreground thread and main entry point
int main(int argc, char *argv[]) {
    int ret;
    int status;
    for (int i = 0; i < 5; i++) {
        ret = pthread_create(&threads[i], NULL, adder, (void *) i);
        if (ret < 0) {
            perror("thread create error : ");
            exit(0);
        }
        ret = pthread_join(threads[i], (void**)&status);
        printf("%d\n", i);

        //printf("%d, %d\n", i, threads[i]);
    }

    // Wait for background thread to finish
//    for (int i = 5 ; i > 0; i--) {
//        ret = pthread_join(threads[i], (void**)&status);
//        printf("%d\n", i);
//    }
    // Show the result from background and foreground threads
    printf("sum all %d\n", sum);
    return 0;
}

