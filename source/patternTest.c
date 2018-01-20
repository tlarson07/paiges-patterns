#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Configure difficulty
// TODO: make it easier to change the difficulty of the program with levels
#define SLOPE_MAX 5 		     // positive
#define SUPPORT_DIV 1 		  // yes (1) or no (0)
#define Y_INT_MAX 4		     // positive or negative (allows support for subtraction)
#define TBL_START_VAL_MAX 5  // positive or negative
#define STEP_MAX 3		     // value betwen consecutive 'input' values
#define NUM_TBL_VALS 5		  // number of lines printed
#define ANSWER_MAX 12		
// Available Colors
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

// Configure Colors
#define PROBLEM_NUM RED
#define PROMPT_SOLUTION GREEN
#define MESSAGES BLUE

// Function prototypes
int randomSign (int num);
void get_yInt(int *yInt);
void get_slope(int *slope);
void get_operator(int *operator);
void printTable(int slope, int yInt, int *operator, int *step, int count);
void getSolution(int slope, int yInt, int operator, char *sign, int step, char *answer);
void checkAnswer(char * yourAnswer, char *answer, int slope, int yInt, int operator, char sign);
int parseAnswer(char *yourAnswer, int slope, int yInt, int operator, char sign);


int main(int argc, char *argv[]){
  /* LOCAL VARIABLES */
  int valid; 	    // TODO: ask the user if they want to continue based on getting 5 in a row correct
  int count; 	    // number of problems
  int start; 	    // start of table
  int step;	       // value between consecutive input values
  int operator;    // multiply (1) or divide (0)
  int slope;	    // slope (multiplied or divided based on operator)
  int yInt;	       // y-intercepti
  char sign;
  char name[50];
  char yourAnswer[ANSWER_MAX];  // user's answer
  char answer[ANSWER_MAX];	   // correct answer

  /* HEADER */
  printf("-------------------- PATTERN PRACTICE --------------------\n");
  printf("Please enter your name: ");
  fgets(name, 50, stdin);
  printf("Welcome %sThis program will generate a table of numbers.\nFind the equation and test all your answers!\nNOTE: type 'new' to get a new problem if your are stuck\n", name);
  printf("-----------------------------------------------------------\n\n");

  /* FOREVER MATH */
  valid = 1;
  count = 1;
  while(valid){
    get_slope(&slope);
    get_yInt(&yInt);
    get_operator(&operator);
    //TODO: consider whether this implementation makes sense...
    printTable(slope, yInt, &operator, &step, count);
    getSolution(slope, yInt, operator, &sign, step, answer);
    checkAnswer(yourAnswer, answer, slope, yInt, operator, sign);
    count++;
  }
  // TODO: print stats
}

// returns copy of given num with random sign
int randomSign (int num){
  if(rand()%2)
    return num * - 1;
  return num;
}

void get_yInt(int * yInt){
  // TODO: add support for choice
  *yInt = randomSign(rand() % Y_INT_MAX);
}

void get_slope(int *slope) {
  // TODO: add support for negative slope
  *slope = rand() % SLOPE_MAX + 1;
}

void get_operator(int *operator) {
   if(SUPPORT_DIV)
      *operator = rand() % 2;
   else
      *operator = 1;
}

void printTable(int slope, int yInt, int *operator, int *step, int count) {
  int i;       // iterator
  int start;   // first input value
  int value;	// output value
  int r;       // temp remainder

  //adjust start value for 'valid' division
  start = randomSign(rand() % TBL_START_VAL_MAX);
  if(!(*operator)){
    r = start % slope;
    if(!r)
      start += r;
    *step = slope;
  }
  else
    *step = rand() % STEP_MAX + 1;

  printf(PROBLEM_NUM "Problem #%d\n" RESET, count);
  for(i=start; i<start + (*step * NUM_TBL_VALS); i += *step){
    // multiply or divide -- THIS DOESN'T MAKE SENSE
    if(*operator)
      value = i * slope;
    else
      value = i / *step;
    // add or subtract y-intercept
    value += yInt;
    // print table
    printf("%6d\t%6d\n", i, value);
  }
  printf("%6c\n", 'n');
}

void getSolution(int slope, int yInt, int operator, char *sign, int step, char *answer) {
   char op;

   if(yInt < 0)
     *sign = '-';
   else
     *sign = '+';
   if(operator)
     op = '*';
   else
     op = '/';
   //  slope = step;
   /*if(slope == 1){
     snprintf(answer, sizeof(answer), "n %c %d\n", *sign, abs(yInt));
   }
   else*/
     snprintf(answer, sizeof(answer), "n%c%d %c %d\n", op, slope, *sign, abs(yInt));
}

// prompt until solution correct or user types "new"
void checkAnswer(char * yourAnswer, char *answer, int slope, int yInt, int operator, char sign)
{
    char new[] = "new";
    printf(PROMPT_SOLUTION "Please enter your answer: " RESET);
    //strcpy(answer, "3n -1");
    fgets(yourAnswer, ANSWER_MAX, stdin);
    // TODO: parse all kinds of input
    while(parseAnswer(yourAnswer, slope, yInt, operator, sign) != 0){
      if(strcmp(yourAnswer, new) == 0){
        printf(BLUE "\nhere is a new problem\n" RESET);
        printf("here was the solution: %s\n", answer);
        return;
      }
      printf(PROMPT_SOLUTION "Keep trying: " RESET);
      fgets(yourAnswer, ANSWER_MAX, stdin);
    }
    printf(MESSAGES "Keep up the good work :)\n\n" RESET);
}

// compare user input with correct solution
int parseAnswer(char *yourAnswer, int slope, int yInt, int operator, char sign)
{
  int i; 
  char *token;
  int mySlope;
  int myYint;
  int myOperator; 
  int mySign; 
  int opFound; 
  int spFound;
  int yFound; 
  int siFound; 

  //init search parameters
  opFound = siFound = spFound = yFound = 0;

  /*opFound = 0; 
  siFound = 0; 
  if(slope != 1) 
    spFound = 0;
  else{ 
    spFound = 1;
    mySlope = 1; 
  }
  if(yInt) 
    yFound = 0;
  else 
    yFound = 1;*/

  //printf("YOUR INPUT: %s", yourAnswer);
  token = strtok(yourAnswer, " \n(){}[]");
  
  //check remaining tokens
  while(token){
  //printf("TOKEN: '%s';\n", token);
   for(i = 0; i<(int)strlen(token); i++){
   
      int a = *(token+i);
      //printf("CHECKING THE FOLLOWING CHAR: %c\n", a);
      if (a == '+'){ 
        mySign = '+';
        siFound = 1; 
      } 
      else if(a == '-') {
        mySign = '-';
        siFound = 1; 
      }
      else if (a == '*'){
        myOperator = 1; 
        opFound = 1; 
      }
      else if (a == '/'){
        myOperator = 0;
        opFound = 1; 
      }
      else if(a - 48 == slope && !spFound && !siFound){
        mySlope = slope; 
        spFound = 1; 
      }
      else if (a - 48 == abs(yInt) && !yFound) { 
        myYint = yInt;
        yFound = 1; 
      }
    }
    token = strtok(NULL, " \n(){}[]");
  }

  // set default operator
  if(!opFound)
    myOperator = 1; 
  if(slope == 1)
    operator = 1; 
  // set default sign & yInt
  if(!siFound){
    mySign = '+'; 
    myYint = 0;
  }
  // set default slope
  if(!spFound)
    mySlope = 1;

  /*printf("\nSLOPE: %d;%d:\n", mySlope, slope);
  printf("Y-INT: %d;%d;\n", myYint, yInt);
  printf("OPERATOR: %d;%d;\n", myOperator, operator);
  printf("SIGN: %d;%d;\n", mySign, sign);*/
  if(mySlope == slope 
	&& myYint == yInt
	&& myOperator == operator
        && mySign == sign) 
    return 0; 
  return 1; 
}
