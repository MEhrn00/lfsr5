/*
	MATH 2190 Project
	Name: Matt Ehrnschwender
	Due Date: 4/9/2020

	Outline:
		- This is a C program that takes in a plaintext file and encrypts it using LFSRsum
		with a user specified seed.
*/

#include "lfsrcrypto.h"

int main(int argc, char* argv[]) {

	FILE* inFile = NULL;
	FILE* outFile = NULL;

	long inFileSize;
	uint8_t* key = NULL;
	char* data = NULL;
	char lfsr5[5];

	// Check to see if the user specifies a plaintext file and if not exit
	if (argc < 3) {
		fprintf(stderr, "Name of the plaintext file and encrypted text file not specified.\n");
		exit(EXIT_FAILURE);
	}

	// Prompt the user to enter the seed for LFSR-5 register
	printf("Enter the LFSR-5 seed: ");
	scanf("%s", lfsr5);

	// Check to see if the seed length is 5 and if not exit
	if(strlen(lfsr5) != 5) {
		fprintf(stderr, "Seed is not 5 characters.\n");
		exit(EXIT_FAILURE);
	}

	// Check to see if the seed entered is a binary number and exit if otherwise
	for (int i = 0; i < 5; i++) {
		if ((int)lfsr5[i] - 48 != 0 && (int)lfsr5[i] - 48 != 1) {
			fprintf(stderr, "Seed is not a binary number.\n");
			exit(EXIT_FAILURE);
		}
	}

	// Open the plain text file that the user specifies
	inFile = fopen(argv[1], "rb");

	// Check to see if the file opened successfully
	if (inFile == NULL) {
		fprintf(stderr, "Error opening plaintext file.\n");
		exit(EXIT_FAILURE);
	}

	// Open the output file to store the encrypted data
	outFile = fopen(argv[2], "wb");

	// Check to see if the file opened successfully
	if (outFile == NULL) {
		fprintf(stderr, "Error opening output file.\n");
		exit(EXIT_FAILURE);
	}

	// Calculate the size of the plain text file and store it
	fseek(inFile, 0, SEEK_END);
	inFileSize = ftell(inFile);
	rewind(inFile);

	// Allocate some memory in ram to store the plain text
	data = (char *)calloc(inFileSize, sizeof(char));

	// Store the text of the plaintext file into memory
	fread(data, sizeof(char), inFileSize, inFile);

	// Close the plain text file
	fclose(inFile);

	// Allocate memory to store the key
	key = (uint8_t*)calloc(inFileSize, sizeof(uint8_t));

	// Generate the key for encryption
	gen_key(key, lfsr5, inFileSize);

	// Encrypt the data
	encrypt_data(data, key, inFileSize);

	// Write the encrypted data to the output file
	fwrite(data, inFileSize, sizeof(char), outFile);

	// Close the output file
	fclose(outFile);

	free(data);

	return 0;
}
