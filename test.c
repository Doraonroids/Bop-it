#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
  int start =0;
  int action =0;
  int score =0;
  int input =0;
  printf("Start game?\n");
  scanf("%d", &start);

  while(start==1){

    action = rand()%3;
    
    switch(action){
      case 0: 
	      printf("Case 0\n");
              printf("Start game?\n");
              scanf("%d",&start);

	      if(start){
	      }
	      break;
      
      case 1: printf("Case 1\n"); 
              printf("Start game?\n");
	      scanf("%d",&start);


	      break;
      case 2: printf("Case 2\n");
              printf("Start game?\n");
	      scanf("%d", &start);


	      break;
      
      case 3: printf("Case 3\n");
              printf("Start game?\n");
              scanf("%d", &start);


	      break;

    }

    printf("Start game?\n");
    scanf("%d",&start);
  }
return 0;
}

