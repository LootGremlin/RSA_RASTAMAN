#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int checkPrime(int n);
int findGCD(int n1, int n2);
int powMod(int a, int b, int n);
void encrypt(int p, int q, char msg[]);
void decipher(int p, int q, unsigned char msg[]);

int main(int argc, char* argv[]) {
	int p, q, e;
	int n, phin, flag, i, count;
	char msg[50];
	int data, cipher[50],decrypt[50];

	/*---------------- PRIME NUMBER ENTRY -----------------------*/
	do{
		printf("\nEnter first prime number for (p): \n");
		scanf("%d",&p);
	
		flag=checkPrime(p);
		if(flag==0) {
			printf("\nNot a prime number! Press enter to try again...\n");
			getch();
		}
		system("cls");
	}while(flag == 0);
	
	do{
		printf("\nEnter another prime number for (q): \n");
		scanf("%d",&q);
	
		flag=checkPrime(q);
		if(flag==0) {
			printf("\nNot a prime number! Press enter to try again...\n");
			getch();
		}
		system("cls");
	}while(flag == 0);
	
	/*-------------TO ENCRYPT WORD ENTRY-------------*/
	printf("Value of p: %d\nValue of q: %d\n\n", p, q);

	printf("Enter a word: ");
	scanf("%s", msg);
	
	/*---------------ENCRYPT & DECRYPT SIMULATION-------------------*/
	encrypt(p, q, msg);
	
	return 0;
}

int checkPrime(int n) {
	int i;
	int m = n / 2;
	
	for (i = 2; i <= m; i++) {
		if (n % i == 0) {
			return 0; // Not Prime
		}
	}

	return 1; // Prime
}

int findGCD(int n1, int n2) {
	int i, gcd;

	for(i = 1; i <= n1 && i <= n2; ++i) {
		if(n1 % i == 0 && n2 % i == 0)
			gcd = i;
	}

	return gcd;
}

int powMod(int a, int b, int n) {
	int x = 1, y = a;

	while (b > 0) {
		if (b % 2 == 1)
			x = (x * y) % n;
		y = (y * y) % n; // Squaring the base
		b /= 2;
	}

	return x % n;
}

void encrypt(int p, int q, char msg[])
{
	int e, count, i, n, phin;
	unsigned char cipher[50];
	
	count=0;
	n = p * q;
	phin = (p - 1) * (q - 1);
	
	for (e = 2; e < n; e++) {
		if (findGCD(phin, e) == 1)
			break;
	}
	
	printf("\n");
	for(i = 0; i < strlen(msg); i++){
		cipher[i] = powMod(msg[i], e, n);
	}
	cipher[i] = '\0';
	
	printf("Ciphered Word: %s\n", cipher);
	
	decipher(p, q, cipher);
}

void decipher(int p, int q, unsigned char msg[])
{
	int d, e, i, n, phin;
	char decrypt[50];
	
	n = p * q;
	phin = (p - 1) * (q - 1);
	
	for (e = 2; e < n; e++) {
		if (findGCD(phin, e) == 1)
			break;
	}
	
	for (d=1; d<n ; d++)
		if ((d*e)%phin==1) 
		break;
	
	fflush(stdin);
	printf("\n");
	for(i = 0; i < strlen(msg); i++){
		decrypt[i] = powMod(msg[i], d, n);
	}
	decrypt[i] = '\0';
	
	printf("Deciphered Word: %s\n", decrypt);
}
