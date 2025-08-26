#include <stdio.h>
#define MS 10

typedef struct {
    float coeff;
    int exp;
} poly;

int main() {
    poly a[MS], b[MS], c[2*MS];
    int na, nb;

    printf("Enter number of terms in 1st polynomial: ");
    scanf("%d", &na);
    printf("Enter coeff and exponent for 1st polynomial (in descending order of exponents):\n");
    for (int i = 0; i < na; i++) {
        scanf("%f %d", &a[i].coeff, &a[i].exp);
    }

    printf("Enter number of terms in 2nd polynomial: ");
    scanf("%d", &nb);
    printf("Enter coeff and exponent for 2nd polynomial (in descending order of exponents):\n");
    for (int i = 0; i < nb; i++) {
        scanf("%f %d", &b[i].coeff, &b[i].exp);
    }

    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i].exp > b[j].exp) {
            c[k] = a[i];
            i++; k++;
        }
        else if (a[i].exp < b[j].exp) {
            c[k] = b[j];
            j++; k++;
        }
        else {
            c[k].exp = a[i].exp;
            c[k].coeff = a[i].coeff + b[j].coeff;
            i++; j++; k++;
        }
    }
    while (i < na) {
        c[k] = a[i];
        i++; k++;
    }
    while (j < nb) {
        c[k] = b[j];
        j++; k++;
    }

    printf("1st polynomial: ");
    for (int l = 0; l < na; l++) {
        printf("%.1fx^%d", a[l].coeff, a[l].exp);
        if (l < na - 1) printf(" + ");
    }
    printf("\n");

    printf("2nd polynomial: ");
    for (int l = 0; l < nb; l++) {
        printf("%.1fx^%d", b[l].coeff, b[l].exp);
        if (l < nb - 1) printf(" + ");
    }
    printf("\n");

    printf("Sum polynomial: ");
    for (int l = 0; l < k; l++) {
        printf("%.1fx^%d", c[l].coeff, c[l].exp);
        if (l < k - 1) printf(" + ");
    }
    printf("\n");

    return 0;
}
