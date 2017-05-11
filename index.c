/*
  Margot Duek Kalach and Jacobo Calderon Miklos
  Advanced programming
  A01021226 and A01021795
  Final Project
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <omp.h>

#define BUFFER_SIZE 255
#define IMAGE 50

int keep_going = 1;

void *recognize_image(void * arg);
void * user_interaction(void * arg);
void * competition();
void * recognize_image_comp(void * arg);
void printDir();

int main(){
  int status;
  void * void_varible;


  pthread_t user_thread; //thread variable

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

//Manu for the user
void * user_interaction(void * arg){
  int op = 0;
  int status;
  void * void_varible;
  pthread_t image_recognizer;

  printf("Hello, welcome to iamyoureyes\n With me you will be able to recognize and know many new things\n");

  while(keep_going > 0 && keep_going < 10){
    printf("\nchoose the option you want\n 1.- Image recognition\n 2.- List images directory\n 3.- image competition\n 0.- exit/quit\n\n");
    scanf("%d", &op); //Waitting for the user
    if(op == 1){
      recognize_image(void_varible);
    }else if(op == 2){
	     printDir();
    }else if(op == 3){
      competition();
    }else if(op == 0){
      keep_going = 0;
    }else{
       printf("Please chose a valid option \n");
    }
  }
}

//Function to call the Python file
void *recognize_image(void * arg){

  char * command1 = "python classify_image.py --image_file images/"; //File name plus images directory specification.
  char command2[IMAGE];
  printf("please type the name of the image you want to analyze as it is (exaple: car.jpg)\n" );
  scanf("%s", command2);

  char * command = (char *) malloc(1 + strlen(command1)+ strlen(command2) );
  strcpy(command, command1);
  strcat(command, command2);

  FILE * file_ptr = NULL;
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

  keep_going = 7;

}


void * competition(){
  int op = 0;
  int status;
  void * void_varible;
  pthread_t pic_1, pic_2;

  char * command1 = "python classify_image.py --image_file images/";
  char command2[IMAGE];
  printf("please type the name of the first image you want to analyze as it is (exaple: car.jpg)\n" );
  scanf("%s", command2);
  char * command = (char *) malloc(1 + strlen(command1)+ strlen(command2) );
  strcpy(command, command1);
  strcat(command, command2);

  char * command12 = "python classify_image.py --image_file images/";
  char command22[IMAGE];
  printf("please type the name of the first image you want to analyze as it is (exaple: car.jpg)\n" );
  scanf("%s", command22);
  char * commandb = (char *) malloc(1 + strlen(command12)+ strlen(command22) );
  strcpy(commandb, command12);
  strcat(commandb, command22);

  status = pthread_create(&pic_1, NULL, &recognize_image_comp, &commandb);
  if (status){
    fprintf(stderr, "ERROR: pthread_create %d\n", status);
    exit(EXIT_FAILURE);
  }
  printf("Created image recognizer thread \n");

  status = pthread_create(&pic_2, NULL, &recognize_image_comp, &command);
    if (status){
      fprintf(stderr, "ERROR: pthread_create %d\n", status);
      exit(EXIT_FAILURE);
    }
    printf("Created image recognizer thread \n");


  keep_going = 1;
}

void * recognize_image_comp(void * arg){
  char * command = &(*(char *)arg);
  printf("\n command : %s \n", command );
  FILE * file_ptr = NULL;
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


void printDir()
{

	DIR *dir; //Directory variable
	struct dirent *sd; //Library structure

	dir = opendir("./images"); //Open images directory

	//If no directory, exit
	if(dir == NULL)
	{
		printf("Error! Directory not located.\n");
		exit(1);
	}

	#pragma omp parallel private(sd)
	{
		//As long as there is a next file, print it
		while((sd=readdir(dir)) != NULL)
		{
			#pragma omp task //firstprivate(sd)
				printf(">> %s\n", sd->d_name);
		}
	}

	closedir(dir); //Close directory

}
