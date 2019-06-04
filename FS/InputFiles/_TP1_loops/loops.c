#include <stdio.h>

int main(){
	int i = 0;
	int final_iter = 1000;
	for(i = 0; i < final_iter; i++){
		printf("%d\n",(i + final_iter)%final_iter);
	}
	return 0;
}
