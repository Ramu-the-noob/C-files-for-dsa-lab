#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//polynomial struct
typedef struct {
	int coeff;
	int exp;
} Term;

//make polynomial functions
readpoly(Term poly[], int n) {
	int i = 0;
	printf("enter coeff and exp for polynomial in descending order : \n");
	while (i < n) {
		printf("enter coefficient %d : ", i + 1);
		scanf_s("%d", &poly[i].coeff);
		printf("enter exponent %d : ", i + 1);
		scanf_s("%d", &poly[i].exp);
		i++;
	}
}

//add function
int polyadd(Term poly1[], Term poly2[], Term sumpoly[], int n1, int n2) {
	int i = 0, j = 0, k = 0;
	while(i< n1 && j< n2) {
		if (poly1[i].exp > poly2[j].exp) {
			sumpoly[k] = poly1[i];
			i++;
			k++;
		}
		else if (poly1[i].exp < poly2[j].exp) {
			sumpoly[k] = poly2[j];
			j++;
			k++;
		}
		else {
			sumpoly[k].coeff = poly1[i].coeff + poly2[j].coeff;
			sumpoly[k].exp = poly1[i].exp;
			i++;
			j++;
			k++;
		}
	}	
	while(i<n1) {
		sumpoly[k] = poly1[i];
		i++;
		k++;
	}
	while (j < n2) {
		sumpoly[k] = poly2[j];
		j++;
		k++;
	}
	return k;
}

//display function
void displaypoly(Term poly[], int n) {
	int i;
	printf("the resultant polynomial is : \n");
	for (i = 0; i < n; i++) {
		printf("%dx^%d ", poly[i].coeff, poly[i].exp);
		if (i != n - 1) {
			printf("+ ");
		}
	}
	printf("\n");
}
//main function
int main() {
	
	Term poly1[50], poly2[50], sumpoly[50];

	int n1;
	printf("enter number of terms in polynomial1 : ");
	scanf_s("%d",&n1);
	readpoly(poly1,n1);
	
	int n2;
	printf("enter number of terms in polynomial2 : ");
	scanf_s("%d",&n2);
	readpoly(poly2, n2);
	
	int k = polyadd(poly1, poly2, sumpoly, n1, n2);
	displaypoly(sumpoly, k);
	return 0;
}
