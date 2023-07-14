#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
 
// Declare two semaphores, one for salad and one for milk
sem_t salad_check, milk_check;

// Function Declarations
void *print_produce( void * );
void *print_dairy( void * );

// Function to print dairy items
void *print_dairy(void *items)
{
    //Variables
    int i = 0;
    char **array = (void *)items;
 
    {
        // Print the dairy item
        printf("got %s\n", (array[i++]));
        // Signal that salad is now available
        sem_post(&salad_check);
        // Wait for milk
        sem_wait(&milk_check);
        // Print rest of diary
        printf("got %s\n", (array[i++]));
        // Signal that salad is now available
        sem_post(&salad_check);
    }
    return (NULL);
}
 
// Function to print produce items
void *print_produce(void *items)
{
    // Variables
    int i = 0;
    char **array = (void *)items;

    {
        // Print the produce item
        printf("got %s\n", (array[i++]));
        // Signal that milk is now available
        sem_post(&milk_check);
        // Wait for salad
        sem_wait(&salad_check);
        // Print rest of produce items
        printf("got %s\n", (array[i++]));
        // Signal that milk is now available
        sem_post(&milk_check);
    }
    return (NULL);
}
 
int main()
{
    // Define two arrays, one for produce and one for dairy
    char *produce[] = {"Salad", "Apples", NULL};
    char *dairy[] = {"Milk", "Butter", NULL};
    pthread_t th1, th2;
    
    // Initialize the semaphores
    sem_init(&salad_check, 0, 0);
    sem_init(&milk_check, 0, 0);
 
    // Create two threads, one for each function
    pthread_create(&th1, NULL, print_produce, (void *)produce);
    pthread_create(&th2, NULL, print_dairy, (void *)dairy);
    
    // Wait for the threads to finish
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
 
    // Destroy the semaphores
    sem_destroy(&salad_check);
    sem_destroy(&milk_check);

    return 0;
}
