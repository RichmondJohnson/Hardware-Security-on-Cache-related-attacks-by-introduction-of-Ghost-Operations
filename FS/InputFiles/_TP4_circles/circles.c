#include <stdio.h>

float cir (float r);

float area(float r);

int main()
{
float circumference,areas,r;
printf("Enter r : ");
scanf("%f", &r);
circumference =cir(r);
areas=area(r);
printf("Circumference is : %f\n", circumference);
printf("Area is : %f\n", areas);
return areas;
}

float cir (float r)
{
  float c;
  c= (2*3.14*r);
  return c;
}

float area(float r)
{
    
    float a,ci;
    ci=cir(r);
    a=(ci*ci)/(4*3.14);
 return a;   
}

