// -----------------------------------------------------
// CSC371 Advanced Object-Oriented Programming (2024/25)
// 
// (c) Martin Porcheron
//     Thomas Reitmaier
//     thomas.reitmaier@swansea.ac.uk
// -----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "timestables.h"

int main(int argc , char *argv[]) {
	
	int *tablesArray[MAX_TIMES_TABLE];

	// Allocate memory for each times table and generate the values for it.
	int num;
	for (num = 0; num <= MAX_TIMES_TABLE; num++) {
		int *values = malloc(sizeof(int) * MAX_TABLE_SIZE);
		tablesArray[num] = values;
		generateTable(num, values);

	}
	printTables(tablesArray);
	
	// Free memory containing times tables
	for (num = 0; num <= MAX_TIMES_TABLE; num++) {
		free(tablesArray[num]);
	}
	

	return 0;
}

