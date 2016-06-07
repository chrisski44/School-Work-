/*
* ID3 Tag Editor by Chris Skowronski
*
* This file is a simple ID3 tag editor that takes in the media file and 
* any command line arguments that are in the appropriate "-Field Value" pair
* will be able to change the tag on the file.
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Struct Tag:
* Contains all the necessary fields for our id3Tag to be read in at exactly 128 bytes
*/
struct Tag {
	char identifier[3];
	char title[30];
	char artist[30];
	char album[30];
	char year[4];
	char comment[28];
	char zero_byte;
	char track_number[1];
	char genre;

};

FILE *f;

int i;
int k;
char identifier[3];
char title[31];
char artist[31];
char album[31];
char year[5];
char comment[29];
char zero_byte;
char track_number[2];
char genre;
int track;
char response[10];
int j;

char compare[30];

int main(int argc, char *argv[]) {
	struct Tag id;
	f = fopen(argv[1], "r+");

	/*
	* F will return 0 if not able to read in the file from the command line
	*/
	if (f == 0) {
		printf("Not able to read in file \n");
	}
	else {
		/*
		* Puts file pointer to the end of file and then moves it back 128 bytes to be read into our struct
		*/
		fseek(f, -128, SEEK_END);
		fread(&id, sizeof(id), 1, f);
		
		/*
		* Searches for "TAG" to notify that an ID3Tag has been created
		* If the tag has not been created, then a new one is made with all values set to 0
		*/
		if (strncmp(id.identifier, "TAG", 3)) {
			printf("Cannot find the tag \n Updating and adding a new one...");

			strncpy(identifier, "TAG", sizeof(identifier));
			strncpy(id.identifier, identifier, sizeof(id.identifier));

			strncpy(title, "0", sizeof(title));
			strncpy(id.title, title, sizeof(id.title));

			strncpy(artist, "0", sizeof(artist));
			strncpy(id.artist, artist, sizeof(id.artist));

			strncpy(album, "0", sizeof(album));
			strncpy(id.album, album, sizeof(id.album));

			strncpy(year, "0", sizeof(year));
			strncpy(id.year, year, sizeof(id.year));

			strncpy(comment, "0", sizeof(comment));
			strncpy(id.comment, comment, sizeof(id.comment));


			strncpy(id.track_number, "0", 1);
			id.genre = 0;
			id.zero_byte = 0;


			/*
			* Checks to make sure an equal amount of field value pairs for editing are 
			* entered into the command line.
			* If so, the field is read in and the value of that field is adjusted accordingly
			*/
			if (argc > 2 && argc % 2 == 0) {
				for (j = 2; j < argc; j++) {
					if (!strncmp(argv[j], "-Title", strlen(argv[j]))) {
						strncpy(id.title, argv[++j], sizeof(id.title));
					}
					else if (!strncmp(argv[j], "-Artist", strlen(argv[j]))) {
						strncpy(id.artist, argv[++j], sizeof(id.artist));
					}
					else if (!strncmp(argv[j], "-Album", strlen(argv[j]))) {
						strncpy(id.album, argv[++j], sizeof(id.album));
					}
					else if (!strncmp(argv[j], "-Year", strlen(argv[j]))) {
						strncpy(id.year, argv[++j], sizeof(id.year));
					}
					else if (!strncmp(argv[j], "-Comment", strlen(argv[j]))) {
						strncpy(id.comment, argv[++j], sizeof(id.comment));
					}
				}
			}
			/*
			* New tag is written to the file that did not previously contain one
			*/
			fseek(f, 0, SEEK_END);
			fwrite(&id, sizeof(id), 1, f);


		}
		
		if (argc > 2 && argc % 2 == 0) {
			for (j = 2; j < argc; j++) {
				if (!strncmp(argv[j], "-Title", sizeof(argv[j]))) {
					strncpy(id.title, argv[++j], sizeof(id.title));
				}
				else if (!strncmp(argv[j], "-Artist", sizeof(argv[j]))) {
					strncpy(id.artist, argv[++j], sizeof(id.artist));
				}
				else if (!strncmp(argv[j], "-Album", sizeof(argv[j]))) {
					strncpy(id.album, argv[++j], sizeof(id.album));
				}
				else if (!strncmp(argv[j], "-Year", sizeof(argv[j]))) {
					strncpy(id.year, argv[++j], sizeof(id.year));
				}
				else if (!strncmp(argv[j], "-Comment", sizeof(argv[j]))) {
					strncpy(id.comment, argv[++j], sizeof(id.comment));
				}
				else if (!strncmp(argv[j], "-Track Number", sizeof(argv[j]))) {
					strncpy(id.track_number, argv[++j], sizeof(id.track_number));
				}
			}
		}

		/*
		* Puts struct values into auxillary arrays to allow for printing on the screen.
		* Extra null character is added at end to allow printf to function properly
		*/


		strncpy(title, id.title, 30);
		title[31] = '\0';
		printf("Title: %s \n", title);

		strncpy(artist, id.artist, 30);
		artist[31] = '\0';
		printf("Artist: %s \n", artist);

		strncpy(album, id.album, 30);
		album[31] = '\0';
		printf("Album: %s \n", album);

		strncpy(year, id.year, 4);
		year[5] = '\0';
		printf("Year: %s \n", year);

		strncpy(comment, id.comment, 28);
		comment[29] = '\0';
		printf("Comment: %s\n", comment);

		strncpy(track_number, id.track_number, 1);
		track_number[1] = '\0';
		printf("Track Number: %s\n", track_number);


		/*
		* File pointer moves back 128 bytes from end to allow edited tag
		* to be written to the file.
		*
		*/
		fseek(f, -128, SEEK_END);
		fwrite(&id, sizeof(id), 1, f);

	}
	/*
	* File is closed
	*/
	fclose(f);
	return (0);
}
