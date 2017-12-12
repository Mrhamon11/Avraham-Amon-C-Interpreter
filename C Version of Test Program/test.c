#include <stdio.h>

int main(){
	int x, y, z;
	int d;
	char c;

	scanf("%c", &c);
	printf("%c\n", c);

	if(c == 'Z'){
    		printf("%d\n", 1);
	}
	else
		printf("%d\n", 0);
	
	scanf("%d", &x);
	scanf("%d", &y);

	z = x + 2 * y -7;

	d = z / (x + 2 * x);

	printf("%d\n", x);
	printf("%d\n", y + 3 * z);
	printf("%d\n", d - (x - 2));
		
	while(y > 0){
		z = x % y;
		x = y;
		y = z;
	}

	printf("%d\n", x);

	return 0;
}
