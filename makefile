lfsr5: lfsr5.c lfsrcrypto.c plaintext.txt
	clang -g -Wall lfsr5.c lfsrcrypto.c -o lfsr5

run: lfsr5 plaintext.txt
	./lfsr5 plaintext.txt encryptedtext.txt

clean: lfsr5
	rm -f lfsr5 encryptedtext.txt

test: lfsr5
	echo -e "10101" | ./lfsr5 plaintext.txt encryptedtext.txt
	echo "File encryped decrypting and comparing..."
	echo -e "10101" | ./lfsr5 encryptedtext.txt dec.txt
	cmp --silent plaintext.txt dec.txt || echo "Comparison Failed!!!"
