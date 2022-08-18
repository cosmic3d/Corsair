INCLUDES = -I ~/.brew/opt/openssl@1.1/include -L ~/.brew/opt/openssl@1.1/lib -lcrypto -lssl
FILES = src/main.c src/gcd.c src/create_private_key.c
FILES2 = src/crypt.c src/gcd.c src/encrypt.c src/decrypt.c

all:
	$(CC) $(INCLUDES) -o corsair.exe $(FILES)
comp:
	./corsair.exe challenge/1.pem challenge/2.pem challenge/3.pem challenge/4.pem challenge/5.pem challenge/6.pem challenge/7.pem challenge/8.pem challenge/9.pem challenge/10.pem challenge/11.pem challenge/12.pem challenge/13.pem challenge/14.pem challenge/15.pem challenge/16.pem challenge/17.pem challenge/18.pem challenge/19.pem challenge/20.pem challenge/21.pem challenge/22.pem challenge/23.pem challenge/24.pem challenge/25.pem challenge/26.pem challenge/27.pem challenge/28.pem challenge/29.pem challenge/30.pem challenge/31.pem challenge/32.pem challenge/33.pem challenge/34.pem challenge/35.pem challenge/36.pem challenge/37.pem challenge/38.pem challenge/39.pem challenge/40.pem challenge/41.pem challenge/42.pem challenge/43.pem challenge/44.pem challenge/45.pem challenge/46.pem challenge/47.pem challenge/48.pem challenge/49.pem challenge/50.pem challenge/51.pem challenge/52.pem challenge/53.pem challenge/54.pem challenge/55.pem challenge/56.pem challenge/57.pem challenge/58.pem challenge/59.pem challenge/60.pem challenge/61.pem challenge/62.pem challenge/63.pem challenge/64.pem challenge/65.pem challenge/66.pem challenge/67.pem challenge/68.pem challenge/69.pem challenge/70.pem challenge/71.pem challenge/72.pem challenge/73.pem challenge/74.pem challenge/75.pem challenge/76.pem challenge/77.pem challenge/78.pem challenge/79.pem challenge/80.pem challenge/81.pem challenge/82.pem challenge/83.pem challenge/84.pem challenge/85.pem challenge/86.pem challenge/87.pem challenge/88.pem challenge/89.pem challenge/90.pem challenge/91.pem challenge/92.pem challenge/93.pem challenge/94.pem challenge/95.pem challenge/96.pem challenge/97.pem challenge/98.pem challenge/99.pem
leakscors:
	leaks -atExit -- ./corsair.exe challenge/1.pem challenge/2.pem challenge/3.pem challenge/4.pem challenge/5.pem challenge/6.pem challenge/7.pem challenge/8.pem challenge/9.pem challenge/10.pem challenge/11.pem challenge/12.pem challenge/13.pem challenge/14.pem challenge/15.pem challenge/16.pem challenge/17.pem challenge/18.pem challenge/19.pem challenge/20.pem challenge/21.pem challenge/22.pem challenge/23.pem challenge/24.pem challenge/25.pem challenge/26.pem challenge/27.pem challenge/28.pem challenge/29.pem challenge/30.pem challenge/31.pem challenge/32.pem challenge/33.pem challenge/34.pem challenge/35.pem challenge/36.pem challenge/37.pem challenge/38.pem challenge/39.pem challenge/40.pem challenge/41.pem challenge/42.pem challenge/43.pem challenge/44.pem challenge/45.pem challenge/46.pem challenge/47.pem challenge/48.pem challenge/49.pem challenge/50.pem challenge/51.pem challenge/52.pem challenge/53.pem challenge/54.pem challenge/55.pem challenge/56.pem challenge/57.pem challenge/58.pem challenge/59.pem challenge/60.pem challenge/61.pem challenge/62.pem challenge/63.pem challenge/64.pem challenge/65.pem challenge/66.pem challenge/67.pem challenge/68.pem challenge/69.pem challenge/70.pem challenge/71.pem challenge/72.pem challenge/73.pem challenge/74.pem challenge/75.pem challenge/76.pem challenge/77.pem challenge/78.pem challenge/79.pem challenge/80.pem challenge/81.pem challenge/82.pem challenge/83.pem challenge/84.pem challenge/85.pem challenge/86.pem challenge/87.pem challenge/88.pem challenge/89.pem challenge/90.pem challenge/91.pem challenge/92.pem challenge/93.pem challenge/94.pem challenge/95.pem challenge/96.pem challenge/97.pem challenge/98.pem challenge/99.pem
exploit:
	$(CC) $(INCLUDES) -o exploit.exe $(FILES2)
leaksploit:
	leaks -atExit -- ./exploit.exe 1 "As I see another leak I commit suicide"
help:
	@echo Usage:
	@echo make : ./corsair.exe will be generated
	@echo 
	@echo ./corsair.exe example.pem example2.pem ... : Compares all the public keys and tries to do the exploit. A pems folder will be created with the public and private key, in case the exploit succeeds.
	@echo 
	@echo make comp : Uses a series of test pems with the program
	@echo 
	@echo make exploit : A private and a public key in pems folder is required for this to compile.
	@echo 
	@echo ./exploit.exe 1 "message" | cat -e : Encrypts a message for you
	@echo ./exploit.exe 2 "message" | cat -e : Encrypts and decrypts a message for you
	@echo 
	@echo NOTE: The encrypted messages contain unprintable characters, thats why you gotta use | cat -e
