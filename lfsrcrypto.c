#include "lfsrcrypto.h"

// This function generates the lfsr5 key
void gen_key(uint8_t* key,char seed[5], long size) {

	uint8_t c1[2];
	uint8_t c2[2];
	uint8_t c3[2];
	uint8_t c4[2];
	uint8_t c5[2];

	// Since the ascii representation of "0" in binary is 00110000 (48)
	// XORing the ascii "0" with 48 will make it binary/integer 00000000 (0)
	// Likewise, XORing ascii "1" with 48 will make it binary 00000001 (1)
	c5[0] = seed[0] ^ 48;
	c4[0] = seed[1] ^ 48;
	c3[0] = seed[2] ^ 48;
	c2[0] = seed[3] ^ 48;
	c1[0] = seed[4] ^ 48;

	// Generate a key the same number of bits as the plain text
	for (int i = 0; i < size; i++) {

		// Due to memory operations mainly taking place at the byte level (8 bits),
		// Some extra memory manipulation is needed
		// This loop will calculate the c1 register for the key and shift it over
		// More information about this is in the project explanation
		for (int x = 7; x >= 0; x++) {
			c4[1] = c5[0]; // Set the next c4 register to the previous c5 register
			c3[1] = c4[0]; // Set the next c3 register to the previous c4 register
			c2[1] = c3[0]; // Set the next c2 register to the previous c3 register
			c1[1] = c2[0]; // Set the next c1 register to the previous c2 register

			// Calculate the next c5 register by XORing the previous c4, c2, and c1 registers
			c5[1] = c4[0] ^ c2[0] ^ c1[0];

			// Make the old c5, c4, c3, c2, c1 registers the new ones so that the next registers can be calculated
			c5[0] = c5[1];
			c4[0] = c4[1];
			c3[0] = c3[1];
			c2[0] = c2[1];
			c1[0] = c1[1];

			// Store the new calculated c1 register in memory
			key[i] = key[i] ^ c1[0] << x;
		}
	}
}


// This function encrypts the plain text with the key
void encrypt_data(char* data, uint8_t* key, long size) {

	// loop over each chacter and XOR it with the key
	for (int i = 0; i < size; i++) {
		data[i] = data[i] ^ key[i];
	}

}
