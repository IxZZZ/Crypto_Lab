#include "DES_without_lib.h"

int main()
{
    string plaintext = "Welcome to the DES encryption and decryption!";
    cout << plaintext << endl;
    cout << "Input plaintext for encryption: ";
    getline(cin, plaintext);
    DES des_operation;
    des_operation.Auto_Generate_Key();
    cout << "Key(hex): " << des_operation.Key_getter() << endl
         << endl;
    cout << "Plaintext(ASCII): " << plaintext << endl
         << endl;

    cout << "\n-----Encryption-----\n";
    cout << "Hex Plaintext: " << ASCII_to_Hexadecimal(plaintext) << endl
         << endl;
    string ciphertext = des_operation.Encrypt(plaintext);
    cout << "ciphertext: " << ciphertext << endl;

    cout << "\n-----Decryption-----\n";
    string encrypted = des_operation.Decrypt(ciphertext);
    cout << "Encrypt ciphertext (hex): " << encrypted << endl
         << endl;
    cout << "Recorvered ciphertext(text): " << Hexadecimal_to_ASCII(encrypted) << endl;
    return 0;
}