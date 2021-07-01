# Crypto_Lab

# Lab01
Code DES and AES with library cryptopp
Task 1: Coding DES, AES using cryptopp library
Required:
+) Plaintext:  

    - Input from screen;
    
    - Support Vietnamse (using setmod, UTF-16)
    
+) Mode of operations:

  - Select mode from screen (using switch case)
  - Support modes:  ECB, CBC, OFB, CFB, CTR, XTS, CCM, GCM.
+) Secret key and Initialization Vector (IV) select from screen (using switch case)

  Case 1: Secret key and IV are randomly chosen for each run time using random generator using CryptoPP::AutoSeededRandomPool;
  
  Case 2: Input Secret Key and IV from screen
  
  Case 3: Input Secret Key and IV from file
  
 +) OS platform
  - Your code can compile on both Windows and Linux;
+) Performance

  - Report your hardware resources
  - Report computation performance for all operations on both Windows and Linux 

[Performance](Lab01/README.md)
# Lab02 

Code DES and DES with out library
Required:
+) Plaintext: 

    - Input from screen;
    
    - Support Vietnamese (using _setmode, UTF-16)
+) Mode of operations

     Using CBC mode
+) Secret key and Initialization Vector (IV)

     Input Secret Key and IV from screen

# Lab03 

Code RSA Cipher (Encryption/Decryption) using CryptoPP

Required:

+) Separation Encryption function and Decryption function (using switch case)

+) Plaintext:

    - Support Vietnamese (UTF-16)
    
    - Input from screen or from file (using switch case)
    
+) Cyphertext:

    - Input from screen or from file (using switch case)
    
+) Secret key/public key

    - The keys load from files (for both two functions)
    
    - The public key: >= 3072 bits
    
 +) OS platforms
 
  - Your code can compile on both Windows and Linux
  
+) Performance

  - Report your hardware resources
  
  - Report computation performance for all operations on both Windows and Linux 
  
  [Performance](Lab03/README.md)
  
  # Lab04
  
  Code ECC-based Digital signature with CryptoPP
  
  Required:
  
+) Algorithm: ECDSA

+) Separation the signing function and the verify function (using switch case)

+) signing function; verify function

    - May adopt from library or direct compute from formulas. Deploy directly from formulas will get 10/100 bonus points. 
    
+) Message to sign: 

    - Input from file
    
    - Support Vietnamese (using UTF-16)
    
+) ECC curve:  should select from standard curves

+) Secret key/public key

    - The keys load from files (for both two functions)
    
    - The public key: >= 256 bits
+) OS platforms

  - Your code can compile on both Windows and Linux

+) Performance

  - Report your hardware resources
  
  - Report computation performance for all operations on both Windows and Linux
  
  [Performance](Lab04/README.md)


# Lab05

Required:

+) Separation all hash functions using switch case:

SHA224, SHA256, SHA384, SHA512, SHA3-224, SHA3-256, SHA3-384, SHA3-512, SHAKE128,SHAKE256 

+) Plaintext:

    - Support Vietnamese (UTF-16)
    
    - Input from screen or from file (using switch case)
+) Digest:

    - may choose digest output length d for SHAKE128,SHAKE256 from screen;
    
    - digest should be encoded as hex string;
+) OS platforms

  - Your code can compile on both Windows and Linux;
  
+) Performance

[Perfomance](Lab05/README.md)

  - Report your hardware resources
  
  - Report computation performance for all operations on both Windows and Linux 

# Lab06 

[Report](Lab06/README.md)

Required:

6.1 MD5 collision attacks

+) Two collision messages have the same prefix string

 - Generate yourself prefix string
 
 - Compute the two output files that have the same MD5 digest (using hashclash tool)
 
+) Two different C++ programs but have the same MD5;

 - Code yourself two short C++ programs
 
 - Compiler your codes code1, code2
 
 - Run hashclash to generate two program with the same MD5 digest
 
Note: It takes long time to generate the output.

6.2 Length extension attacks on MAC using SHA256 in form: SHA256(k||m), k is secret key

 - This one for bonus 10/100 points (does not require all students)
 
+) Coding self programs that can
 - Automatic compute the padded part for any input (k||m);
 
 - Compute the digest using length extension attacks with any extend string;
