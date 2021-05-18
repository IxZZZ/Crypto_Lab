#include "AES_without_lib.h"

int main()
{
     string plaintext = "Welcome to the AES encryption and decryption!";
     AES aes;
     aes.Auto_Generate_Key();
     cout << plaintext << endl;
     cout << "Input plaintext to encryption: ";
     getline(cin, plaintext);
     cout << endl;
     cout << "Plaintext(ASCII): " << plaintext << endl
          << endl;
     cout << "Key(hex): " << aes.Key_getter() << endl;
     cout << "\n\n----Encryption-----\n";
     string ciphertext = aes.Encryption(plaintext);
     cout << "Ciphertext(hex): " << ciphertext << endl;
     string recovered = aes.Decryption(ciphertext);
     cout << "\n\n-----Decryption-----\n";
     cout << "Recovered(hex): " << recovered << endl
          << endl;
     cout << "Recovered(ASCII): " << Hexadecimal_to_ASCII(recovered) << endl;
     return 0;
}
//test->  Input iterators to the initial and final positions in a range. The range used is [first,last), which includes all the characters between first and last, including the character pointed by first but not the character pointed by last.The function template argument InputIterator shall be an input iterator type that points to elements of a type convertible to char.