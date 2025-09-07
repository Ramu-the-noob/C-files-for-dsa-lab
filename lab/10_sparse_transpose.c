#include <stdio.h>
#include <stdlib.h>

struct sparse {
	int col;
	int row;
	int val;
};

void transpose(struct sparse* a, struct sparse* t, int values);
int main() {
	// sparse matrix creation
	printf("enter the number of elements in the sparse matrix : ");
	int values;
	scanf_s("%d", &values);

	// value struct
	struct sparse* a = (struct sparse*)malloc(values * sizeof(struct sparse));

	// inserting values
	for (int i = 0; i < values; i++) {

		printf("enter row : ");
		scanf_s("%d", &a[i].row);

		printf("enter column : ");
		scanf_s("%d", &a[i].col);

		printf("enter value : ");
		scanf_s("%d", &a[i].val);

	}

	//display original
	printf("original matrix : \n");
	printf("row\t column\t values\n");
	for (int j = 0; j < values; j++) {
		printf("%d \t %d \t %d\n", a[j].row, a[j].col, a[j].val);
	}
	
	// Allocate memory for transpose
	struct sparse* t = (struct sparse*)malloc(values * sizeof(struct sparse));

	// Call transpose function
	transpose(a, t, values);

	// Display transposed matrix
	printf("transposed matrix : \n");
	printf("row\t column\t values\n");
	for (int j = 0; j < values; j++) {
		printf("%d \t %d \t %d\n", t[j].row, t[j].col, t[j].val);
	}

	free(a);
	free(t);
	return 0;
}

	//transpose
	void transpose(struct sparse *a, struct sparse *t, int values){
		
		int k = 0;

		// swapper
		for (int i = 0; i < values; i++) {
			// Swap row and column
			t[k].row = a[i].col;
			t[k].col = a[i].row;
			t[k].val = a[i].val;
			k++;
		}
		// organiser
		for (int i = 0; i < values - 1; i++) {
			for (int j = i + 1; j < values; j++) {
				if (t[i].row > t[j].row ||
					(t[i].row == t[j].row && t[i].col > t[j].col)) {
					struct sparse temp = t[i];
					t[i] = t[j];
					t[j] = temp;
				}
			}
		}
	}

	

