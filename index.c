/*
  Margot Duek Kalach and Jacobo Calderon Miclos
  Advanced programming
  A01021226 and A01021795
  Final Project
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUFFER_SIZE 255
#define IMAGE 50

int keep_going = 1;

void *recognize_image(void * arg);
void * user_interaction(void * arg);

int main(){
  int status;
  void * void_varible;


  pthread_t user_thread;

  //we start each thread checking if it was successfully created
  status = pthread_create(&user_thread, NULL, &user_interaction, &void_varible);
  if (status)
    {
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
  printf("Created user thread \n");

  // Wait for all other threads to finish
  pthread_exit(NULL);


  return 0;
}

void * user_interaction(void * arg){
  int op = 0;
  int status;
  void * void_varible;
  pthread_t image_recognizer;

  printf("Hello, welcome to iamyoureyes\n With me you will be able to recognize and know many new things\n");

  printf("choose the option you want\n 1.- Image recognition\n 2.- smt else\n 3.- smt else\n 0.- exit/quit\n\n");
  scanf("%d", &op);
  while(keep_going > 0 && keep_going < 10){
    if(op == 1){
      keep_going = 11;
      status = pthread_create(&image_recognizer, NULL, &recognize_image, &void_varible);
      if (status)
	{
	  fprintf(stderr, "ERROR: pthread_create %d\n", status);
	  exit(EXIT_FAILURE);
	}
      printf("Created image recognizer thread \n");
    }else if(op == 2){
      keep_going = 22;
    }else if(op == 0){
      keep_going = 0;
    }else{
       printf("Please chose a valid option \n");
    }
  }
}



void *recognize_image(void * arg){
  FILE * file_ptr = NULL;
  char * command1 = "python classify_image.py --image_file images/";
  char command2[IMAGE];
  printf("please type the name of the image you want to analyze as it is (exaple: car.jpg)\n" );
  scanf("%s", command2);
  // char * command = malloc(strlen(command1)+strlen(command2)+1);
  //char *strcat(char *command,const char *command2);

  char * command = (char *) malloc(1 + strlen(command1)+ strlen(command2) );
  strcpy(command, command1);
  strcat(command, command2);
  //printf("%s\n", command );
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

  keep_going = 1;

}
