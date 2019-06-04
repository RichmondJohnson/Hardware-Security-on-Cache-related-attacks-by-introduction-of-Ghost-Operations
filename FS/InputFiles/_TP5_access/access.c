#include <stdio.h>

int main()
{
int passkey;
int stored_key = 9721;
int count = 0;
int tolerance_flag = 5;


while(1)
{  
    printf("Enter passkey : ");
    scanf("%d", &passkey);
    
   if (passkey==stored_key)
   {
       break;
   }
   printf("Access Denied\n");
   count++;
   if(count == tolerance_flag){
      printf("Disabled Access\nExiting\n");
      return -1;
}
}

printf("Access Granted\n");
return 0;
}
