/*
  Margot Duek Kalach and Jacobo Calderon Miclos
  Advanced programming
  A01021226 and A01021795
  Final Project
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int main(){
  int status;

  pthread_t user_thread, image_recognizer;

  //we start each thread checking if it was successfully created
  status = pthread_create(&user_thread, NULL, &user_interaction, &void_varible);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created user thread \n");

  status = pthread_create(&image_recognizer, NULL, &recognize_image, &image);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created image recognizer thread \n");


  // Wait for all other threads to finish
  pthread_exit(NULL);


  return 0;
}

void * user_interaction(void * arg){


}
