/*
  Margot Duek Kalach and Jacobo Calderon Miclos
  Advanced programming
  A01021226 and A01021795
  Final Project
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 255

void *recognize_image(void * arg);
void * user_interaction(void * arg);

int main(){
  int status;
  void * void_varible;

  pthread_t user_thread, image_recognizer;

  //we start each thread checking if it was successfully created
  status = pthread_create(&user_thread, NULL, &user_interaction, &void_varible);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created user thread \n");

  status = pthread_create(&image_recognizer, NULL, &recognize_image, &void_varible);
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
  printf("Hello, welcome to iamyoueyes\n With me you will be able to recognize and know many new things\n");

}

void *recognize_image(void * arg){
  FILE * file_ptr = NULL;
  char * command = "python classify_image.py --image_file ~/Pictures/yo.jpg";
  char buffer[BUFFER_SIZE];

  // Open the pipe
  file_ptr = popen(command, "r");
  // Validate that the pipe could be opened
  if (file_ptr != NULL)
  {
      while ( fgets(buffer, BUFFER_SIZE, file_ptr) )
      {
          printf("\t%s", buffer);
      }

      // Close the pipe
      pclose(file_ptr);
  }
}
