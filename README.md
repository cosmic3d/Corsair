# corsair
A program to crack RSA keys.

EXPLOIT INSTRUCTIONS

This tool is designed for trying to exploit the RSA cryptography system.
If you only want to see how you can create a private key using two public certificates, you can just use the ./corsair.exe cert1.pem cert2.pem ... to compare certificates and try to create a private key from them.

Otherwise, if you want to compile the program, you may need to install openssl@1.1 and change the path in my Makefile.

Once you've created a private key, you can use the ./exploit.exe to encrypt and decrypt information

More info with make help
