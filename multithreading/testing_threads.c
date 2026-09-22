/* Original Author: Rahul Jain, GeeeksForGeeks */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* myThread(void* arg){
    while(1){
    printf("Thread is running\n"); 
    sleep(2);
 }
    return NULL; 
}
void explain(void){

    printf("\n\nThe program creates a new thread using pthread_create()"
           "\nThe main thread waits for the created thread to finish using pthread_join()\n");

}

int main(){
    printf("\nWe create a pthread_t variable to store a thread ID\n"); 
    pthread_t thread;
    printf("\nNow we create a new thread using the pthread_create() foo\n\n");
    printf("Syntax >>> pthread_create(thread, attr, routine, arg)\n\n"
            "Parameters\n"

            "thread - Stores the ID of the newly created thread\n"
            "attr - Specifies thread attributes (NULL for default)\n"
            "routine - Function executed by the thread\n"
            "arg - Argument passed to the thread function\n\n");

    pthread_create(&thread,NULL,myThread,NULL); 
    sleep(5);
    printf("Requesting to cancel the thread after 5 seconds\n");
    pthread_cancel(thread);
    pthread_join(thread,NULL);
    printf("\nMain thread finished!\n"); 
    //explain();
    return 0;  
}
