/*
mystrings.c by Chris Skowronski

This program iterates through a text file that is taken in as a parameter
Any string that is considered valid is a valid ASCII character (between 32 and 126 in value) with 4 or more in a row
The file finds these valid strings and prints them to the console.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


FILE *f;
long size;
char *buffer;
char word[4];
int location;
char current_char;
int number_of_bytes;


/*
takes in a character and checks to see if valid

checks to see if value is between 32 and 126
*/
int valid(char c) {
	if (c >= 32 && c <= 126) {
		return 1;
	}
	else {
		return 0;
	}
}

int main(int argc, char *argv[])
{
	//Checks to see that file name was entered 
	if (argc != 2) {
		printf("Please enter a file");
	}
	else {
		//checks if file is valid 
		if ((f = fopen(argv[1], "rb")) != NULL){
			do {
				//keeps track of where location is in file
				location = ftell(f);
				//reads in first 4 bytes
				number_of_bytes = fread(&word, 1, 4, f);
				

				//If 4 characters are not read in, means the end of file 
				if (number_of_bytes != 4) {
					printf("End of file.");
					break;
				}
				else {
					//takes each individual character and checks if 4 in a row are valid

					if((valid(word[0])) && (valid(word[1])) && (valid(word[2]))
						&& (valid(word[3]))){
						fseek(f, location, SEEK_SET);
						while (!(feof(f))) {
							//if they were valid, start from first char and go until you find one that isn't valid
							fread(&current_char, 1, 1, f);
							if (valid(current_char)) {
								//print current char
								printf("%c", current_char);
							}
							else {
								//if not valid, print a new line
								printf("\n");
								break;
							}
						}
					}
					else {
						//if not valid 4 characters, retrace 3 positions to try the start of the next string
						fseek(f, ftell(f) - 3, SEEK_SET);
					}
				}
			} while (!feof(f));
		}
		else {
			printf("Could not open file");
			return 1;
		}
	}
	
    return (0);
}

