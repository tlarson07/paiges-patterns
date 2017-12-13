#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Configure difficulty
// TODO: make it easier to change the difficulty of the program with levels
#define SLOPE_MAX 5 		     // positive
#define Y_INT_MAX 4		     // positive or negative (allows support for subtraction)
#define SUPPORT_DIV 1 		  // yes (1) or no (0)
#define TBL_START_VAL_MAX 5  // positive or negative
#define STEP_MAX 3		     // value betwen consecutive 'input' values
#define NUM_TBL_VALS 5		  // number of lines printed

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
void getSolution(int slope, int yInt, int operator, int step, char *answer);
void checkAnswer(char *yourAnswer, char *answer);
//int parseAnswer(char *yourAnswer, char *answer, int slope, int yInt);


int main(int argc, char *argv[]){
  /* LOCAL VARIABLES */
  int valid; 	    // TODO: ask the user if they want to continue based on getting 5 in a row correct
  int count; 	    // number of problems
  int start; 	    // start of table
  int step;	       // value between consecutive input values
  int operator;    // multiply (1) or divide (0)
  int slope;	    // slope (multiplied or divided based on operator)
  int yInt;	       // y-intercept
  char yourAnswer[12];  // user's answer
  char answer[12];	   // correct answer

  /* HEADER */
  printf("---------- PATTERN PRACTICE ----------\n");
  printf("Welcome Paige! This program will generate a table of numbers.\nFind the equation and test all your answers!!!\nNOTE: type 'new' to get a new problem if your are stuck\n");
  printf("---------------------------------------\n\n");

  /* FOREVER MATH */
  valid = 1;
  count = 1;
  while(valid){
    get_slope(&slope);
    get_yInt(&yInt);
    get_operator(&operator);
    //TODO: consider whether this implementation makes sense...
    printTable(slope, yInt, &operator, &step, count);
    getSolution(slope, yInt, operator, step, answer);
    checkAnswer(yourAnswer, answer);
    count++;
  }
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
  if(*operator){
    r = start % slope;
    if(!r)
      start += r;
    *step = slope;
  }
  else
    *step = rand() % STEP_MAX + 1;

  printf(PROBLEM_NUM "Problem #%d\n" RESET, count);
  for(i=start; i<start + (*step * NUM_TBL_VALS); i += *step){
    // multiply or divide
    if(operator)
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

void getSolution(int slope, int yInt, int operator, int step, char *answer) {
   char sign;
   char op;

   if(yInt < 0)
     sign = '-';
   else
     sign = '+';
   if(operator)
     op = '*';
   else
     op = '/';
     slope = step;
   if(slope == 1){
     snprintf(answer, sizeof(answer), "n %c %d\n", sign, abs(yInt));
   }
   else
     snprintf(answer, sizeof(answer), "n%c%d %c %d\n", op, slope, sign, abs(yInt));
}

// prompt until solution correct or user types "new"
void checkAnswer(char * yourAnswer, char *answer)
{
    char new[] = "new\n";
    printf(PROMPT_SOLUTION "Please enter answer: " RESET);
    fgets(yourAnswer, sizeof(yourAnswer), stdin);
    printf("here was the solution: %s\n", answer);
    return;
    // TODO: parse all kinds of input
    /*while(parseAnswer(yourAnswer, slope, yInt) != 0){
      if(strcmp(yourAnswer, new) == 0){
        printf(BLUE "\nhere is a new problem\n" RESET);
        printf("here was the solution: %s\n", answer);
        return;
      }
      printf(PROMPT_SOLUTION "Keep trying: " RESET);
      fgets(yourAnswer, sizeof(yourAnswer), stdin);
    }
    printf(MESSAGES "Keep up the good work :)\n\n" RESET);*/
}

/* compare user input with correct solution
int parseAnswer(char *yourAnswer, int slope, int yInt, int operator)
{
  char *token;
  int mySlope;
  int myInt;

  token = strtok(yourAnswer, " \n(){}[]";
  if(*token - 48 == slope) {
    mySlope = slope;
  }
  while(token){
    token = strtok(NULL, " \n(){}[]");

  }
}*/
