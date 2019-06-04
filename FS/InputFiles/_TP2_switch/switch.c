#include <stdio.h>

int main()
{
int number;
printf("Enter number between 1 & 5 : ");
scanf("%d", &number);

switch(number)
{
case 1:
      printf("one");
      break;
case 2:
      printf("two");
      break;
case 3:
      printf("three");
      break;
case 4:
      printf("four");
      break;
case 5:
      printf("five");
      break;
default:
      printf("Invalid Number");
      break;
}
printf("\n");
return 0;
}
