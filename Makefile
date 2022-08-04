CC = gcc
INCLUDES = -I ~/.brew/opt/openssl@1.1/include -L ~/.brew/opt/openssl@1.1/lib -lcrypto -lssl
FILES = main.c gcd.c create_private_key.c

all:
	$(CC) $(INCLUDES) -o corsair.exe $(FILES)
comp:
	./corsair.exe challenge/1.pem challenge/2.pem challenge/3.pem challenge/4.pem challenge/5.pem challenge/6.pem challenge/7.pem challenge/8.pem challenge/9.pem challenge/10.pem challenge/11.pem challenge/12.pem challenge/13.pem challenge/14.pem challenge/15.pem challenge/16.pem challenge/17.pem challenge/18.pem challenge/19.pem challenge/20.pem challenge/21.pem challenge/22.pem challenge/23.pem challenge/24.pem challenge/25.pem challenge/26.pem challenge/27.pem challenge/28.pem challenge/29.pem challenge/30.pem challenge/31.pem challenge/32.pem challenge/33.pem challenge/34.pem challenge/35.pem challenge/36.pem challenge/37.pem challenge/38.pem challenge/39.pem challenge/40.pem challenge/41.pem challenge/42.pem challenge/43.pem challenge/44.pem challenge/45.pem challenge/46.pem challenge/47.pem challenge/48.pem challenge/49.pem challenge/50.pem challenge/51.pem challenge/52.pem challenge/53.pem challenge/54.pem challenge/55.pem challenge/56.pem challenge/57.pem challenge/58.pem challenge/59.pem challenge/60.pem challenge/61.pem challenge/62.pem