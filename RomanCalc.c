/*
Daniel Felix-Kim
Roman Numeral Calculator
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void RomAdd (char*); // Function to add and simplify two Roman numerals
void Addexpand (char*); // Function to expand Roman numerals and concatenate 
void RomSubtract (char*); // Function to subtract and simplify two Roman numerals
int counter(char*); // Function to count each appearance of a Roman numeral
int subcountera(char*); // Function to count each appearance of a Roman numeral
int subcounterb(char*); // Function to count each appearance of a Roman numeral in second number during subtraction
int count[7] = {0, 0, 0, 0, 0, 0, 0}; // Counter to keep track of Roman Numerals in order from M to I
int holdcount[7] = {0, 0, 0, 0, 0, 0, 0}; // Counter to keep track of Roman Numerals in order from M to I
int subcounta[7] = {0, 0, 0, 0, 0, 0, 0}; // Counter for subtraction to keep track of Roman Numerals before - sign
int subcountb[7] = {0, 0, 0, 0, 0, 0, 0}; // Second counter for subtraction to keep track of Roman after - sign
int opcheck (char*);   	// Check if adding (1) or subtracting (0)
int operationcheck; // =1 if adding or =0 if subtracting
void simplifya (char*); // Function to finalize Roman Numerals
void simplifyb (char*);
void Subtexpand (char*); // Function to expand Roman numerals and keep separate 



int main(void)
{
	char input [100]; // String that will be inputted
	printf("Enter a number\n"); 
	fgets(input, 100, stdin);
	
	opcheck(input); // Check whether adding or subtracting
	if (operationcheck == 1) // Adding
	{
		Addexpand(input); // Expand the Roman Numerals
		simplifya(input); // Add them into one numeral
		simplifyb(input); // Simplify 
		printf("%s\n", input);  // Print
	}
	else if (operationcheck == 0)  // Subtracting
	{
		Subtexpand(input);  // Expand
		subcountera(input); //Count before - sign
		subcounterb(input); // Count after - sign
		RomSubtract(input); // Subtract
		simplifyb(input);  // Simplify
		printf("%s\n", input); // Print
	}
	else if (operationcheck == 2) 
	{
		printf("Please enter a valid equation\n");
	}
	
	return(0);
}

// ADD Functions
void simplifya (char* r)
{
	int i = 0,j = 0, limit = 0; 
	char *pointer, *result;		// pointer: one for the current string being looked at, and one for the outputted string
	int length = strlen(r);
	const char *index[7]; // index used to create string
	index[0] = "M";
	index[1] = "D";
	index[2] = "C";
	index[3] = "L";
	index[4] = "X";
	index[5] = "V";
	index[6] = "I";
	result = (char*)malloc(length+1);
	
	if (operationcheck == 1)
	{
		for (int v =0; v < 7; v++) // Check Counter
		{
			count[v] = 0;
		}
		counter(r);	
	}
	
	for (i = 6; i >= 0; i--) 
	{
		if ((count[i] >= 2) && ((i == 5) || (i == 3) || (i == 1))) // V, L, D can only appear once
		{
			while (count [i] >= 2)
			{
				count[i]-=2;
				count[i-1]++;
			}
		}
		else if ((count[i] >= 5) && ((i == 6) || (i == 4) || (i == 2))) // I, X, C can only appear less than 5 times. 
		{																// The other cases like 4 are handled in "simplify"
			while (count [i] >= 5)
			{
				count[i]-=5;
				count[i-1]++;
			}
		}
	}
	
	for (int v =0; v < 7; v++) 
	{
		holdcount[v] = count[v];
	}

	for (i = 0; i < 7; i++)  // Write information from counter to create a Roman Numeral String
	{
		while (holdcount [i] > 0) 
		{
			*(result+j) = *index[i];
			j++;
			holdcount[i]--;
		}
	}
	pointer = r;
	*(result+j) = '\0';
	strcpy(r, result);
	free(result);	
}

//Simplify

void simplifyb(char *q)
{
	int i = 0,j = 0, limit = 0; 
	char *pointer, *result;
	int length = strlen(q);
	const char *index[7];
	index[0] = "M";
	index[1] = "D";
	index[2] = "C";
	index[3] = "L";
	index[4] = "X";
	index[5] = "V";
	index[6] = "I";
	result = (char*)malloc(length+1);
	
	for (i = 0; i < 7; i++)
	{
		while (count [i] > 0)
		{
		
			if ((count[i] == 4) && ((i == 6) || (i == 4) || (i == 2)) && (count[i-1] == 0)) // Ex: IIII -> IV
			{
				*(result+j) = *index[i];
				j++;
				*(result+j) = *index[i-1];
				j++;
				count[i] = 0;
			}
			else if ((count[i+1] == 4) && ((i == 5) || (i == 3) || (i == 1)) && (count[i] == 1)) // Ex: VIIII -> IX
			{
				*(result+j) = *index[i+1];
				j++;
				*(result+j) = *index[i-1];
				j++;
				count[i] = 0;
				count[i+1] = 0;
			}
			else
			{
				*(result+j) = *index[i];
				j++;
				count[i]--;
			}
		}	
	}
	pointer = q;
	*(result+j) = '\0';
	strcpy(q, result);
	free(result);	
}

void RomSubtract(char *b)
{
	int i = 0, j = 0, k = 0, d = 1, borrow = 0; 
	char *pointer, *result;		// pointer: one for the current string being looked at, and one for the outputted string
	int length = strlen(b);
	const char *index[7]; // index used to create string
	index[0] = "M";
	index[1] = "D";
	index[2] = "C";
	index[3] = "L";
	index[4] = "X";
	index[5] = "V";
	index[6] = "I";
	result = (char*)malloc(length+1);
	
	for (int v =0; v < 7; v++) // Check Counter
	{
		subcounta[v] = 0;
	}
	subcountera(b);
	for (int v =0; v < 7; v++) // Check Counter
	{
		subcountb[v] = 0;
	}
	subcounterb(b);
	
	for (int v =0; v < 7; v++) // Subtract counters
	{
		count[v] = subcounta[v] - subcountb[v];
	}
	
			
	for (k = 6; k >= 0; k--) 
	{
		if ((count[k] < 0) && (count[k-1] <= 0)) // Borrowing function
		{
			while (count[k-d] <= 0 )
			{
				d++; 
			}
			for (int r = d; r >= 0; r--)
			{
				if (count[k] < 0) // Convert next highest Roman numeral and add to negative counter
				{
					if ((r == 0) || (r == 2) || (r == 4))	
					{
						borrow = 2;
					}
					if ((r == 1) || (r == 3) || (r == 5))	
					{
						borrow = 5;
					}
					count[k-r]--;
					count[k-r+1] = count[k-r+1] + borrow;
				}	
			}
		}
		else // No borrowing needed
		{
			for (int r = 0; r < d; r++)
			{
				if (count[k] < 0)
				{
					count[k-1]--;
					if ((k == 0) || (k == 2) || (k == 4) || (k==6))	
					{
						borrow = 5;
					}
					if ((k == 1) || (k == 3) || (k == 5))	
					{
						borrow = 2;
					}
					count[k] = count[k] + borrow;	
				}	
			}
		}
	d = 1;		
	}

}


void Addexpand(char *s) // Expand function: Scans Roman Numeral equation and concatenates the two numbers
{	
	int i = 0, j = 0, length; // used for counters
	char *pointer, *result; // pointer: one for the current string being looked at, and one for the outputted string
	
	length = strlen(s);
	result = (char*)malloc(length+1);
	pointer = s;
	for (int v =0; v < 7; v++)
		{
			count[v] = 0;
		}
	counter(s);	
	for (i = 0;  i < length; i++) // Expanding Roman Numerals to least simplified
	{
		if ((*pointer == 'I') && ( *(pointer+1)== 'V')) 
		{
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'I';
				j++;
			}
			pointer+=2;
		}
		else if ((*pointer == 'I') && ( *(pointer+1)== 'X'))
		{
			*(result+j) = 'V';
			j++;
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'I';
				j++;
			}
			pointer+=2;
		}
		else if ((*pointer == 'X') && ( *(pointer+1)== 'L'))
		{
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'X';
				j++;
			}
			pointer+=2;
		}	
		else if ((*pointer == 'X') && ( *(pointer+1)== 'C'))
		{
			*(result+j) = 'L';
			j++;
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'X';
				j++;
			}
			pointer+=2;
		}
		else if ((*pointer == 'C') && ( *(pointer+1)== 'D'))
		{
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'C';
				j++;
			}
			pointer+=2; 
		}	
		else if ((*pointer == 'C') && ( *(pointer+1)== 'M'))
		{
			*(result+j) = 'D';
			j++;
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'C';
				j++;
			}
			pointer+=2; 
		}
		else if ((*pointer == ' ') || (*pointer == '+'))
		{
			pointer++;
		}	
		else 
		{
			*(result+j) = *pointer;
			j++;
			pointer++;
		}		
	}
	pointer = s;
		
	*(result+j) = '\0';
	
	strcpy(s, result);
	free(result);
}

//Counter Functions
int counter(char *u) // Counts number of individual characters
{	
	int i = 0, j = 0, k = 0;
	char *pointer, *result;
	const char *index[7];
	index[0] = "M";
	index[1] = "D";
	index[2] = "C";
	index[3] = "L";
	index[4] = "X";
	index[5] = "V";
	index[6] = "I";
	int length = strlen(u);
	
	result = (char*)malloc(length+1);
	
	pointer = u;
	
	for (j = 0; j <7; j++)
	{	
		for (i = 0;  i < (length) ; i++)
		{
			if (pointer[i] == *index[j]) 
			{
				(count[j])++;
				
			}
		}
	}
	return count[7];
}

int subcountera(char *f) // Counts number of individual characters before - sign
{	
	int i = 0, j = 0, k = 0;
	char *pointer, *result;
	const char *index[7];
	index[0] = "M";
	index[1] = "D";
	index[2] = "C";
	index[3] = "L";
	index[4] = "X";
	index[5] = "V";
	index[6] = "I";
	const char *minus = "-";
	int length = strlen(f);
	int newlength = 0;
	
	result = (char*)malloc(length+1);
	
	pointer = f;
	
	for (k = 0; k < length; k++)
	{
		if (pointer[k] == *minus)
		{
			k = length;
		}
		newlength++;
	}
	
	for (j = 0; j <7; j++)
	{	
		for (i = 0;  i < newlength ; i++)
		{
			if (pointer[i] == *index[j]) 
			{
				(subcounta[j])++;
			}
		}
	}
	return subcounta[7];
}


int subcounterb(char *f) // Counts number of individual characters before - sign
{	
	int i = 0, j = 0, k = 0;
	char *pointer, *result;
	const char *index[7];
	index[0] = "M";
	index[1] = "D";
	index[2] = "C";
	index[3] = "L";
	index[4] = "X";
	index[5] = "V";
	index[6] = "I";
	const char *minus = "-";
	int length = strlen(f);
	int newlength = 0;
	
	result = (char*)malloc(length+1);
	
	pointer = f;
	
	for (k = 0; k < length; k++)
	{
		if (pointer[k] == *minus)
		{	
			for (j = 0; j <7; j++)
			{	
				for (i = k;  i < (length) ; i++)
				{
					if (pointer[i] == *index[j]) 
					{
						(subcountb[j])++;	
					}
				}
			}
		}
	}

	return subcountb[7];
}






// Operation Check
int opcheck (char*t)
{
	int i = 0, j = 0, length; // used for loops
	char *pointer, *result; // pointer: current string being looked at; result: the outputted string
	
	length = strlen(t);
	result = (char*)malloc(length+1);
	pointer = t;
	
	for (i = 0;  i < length; i++)
	{
		if ((*pointer == 'I') || (*pointer == 'V') || (*pointer == 'X') || (*pointer == 'L') || (*pointer == 'C') || (*pointer == 'D') || (*pointer == 'M'))
		{
			pointer++;
		}
		else if (*pointer == ' ')
		{
			pointer++;
		}
		else if (*pointer == '+') // Operation is addition
		{
			operationcheck = 1;
		}
		else if (*pointer == '-') // Operation is subtraction
		{
			operationcheck = 0;
		}
		else
		{ 
			operationcheck = 2; // Operation is invalid
		}
	}
	return operationcheck;
}



// Expand for subtraction
void Subtexpand(char *a) // Expand function: 
{	
	int i = 0, j = 0, length; // used for counters
	char *pointer, *result; // pointer: one for the current string being looked at, and one for the outputted string
	
	length = strlen(a);
	result = (char*)malloc(length+1);
	pointer = a;
	for (int v =0; v < 7; v++)
		{
			count[v] = 0;
		}
	counter(a);	
	for (i = 0;  i < length; i++)
	{
		if ((*pointer == 'I') && ( *(pointer+1)== 'V'))
		{
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'I';
				j++;
			}
			pointer+=2;
		}
		else if ((*pointer == 'I') && ( *(pointer+1)== 'X'))
		{
			*(result+j) = 'V';
			j++;
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'I';
				j++;
			}
			pointer+=2;
		}
		else if ((*pointer == 'X') && ( *(pointer+1)== 'L'))
		{
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'X';
				j++;
			}
			pointer+=2;
		}	
		else if ((*pointer == 'X') && ( *(pointer+1)== 'C'))
		{
			*(result+j) = 'L';
			j++;
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'X';
				j++;
			}
			pointer+=2;
		}
		else if ((*pointer == 'C') && ( *(pointer+1)== 'D'))
		{
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'C';
				j++;
			}
			pointer+=2; 
		}	
		else if ((*pointer == 'C') && ( *(pointer+1)== 'M'))
		{
			*(result+j) = 'D';
			j++;
			for (int ii = 0; ii <4; ii++)
			{
				*(result+j) = 'C';
				j++;
			}
			pointer+=2; 
		}
		else if (*pointer == '-')  // Keep so it can be used to separate counters
		{
			*(result+j) = *pointer;
			j++;
			pointer++;
		}
		else if (*pointer == ' ')
		{
			pointer++;
		}		
		else 
		{
			*(result+j) = *pointer;
			j++;
			pointer++;
		}		
	}
	pointer = a;
		
	*(result+j) = '\0';
	
	strcpy(a, result);
	free(result);
}







