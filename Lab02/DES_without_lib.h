#include <iostream>
#include <random>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
wstring string_to_wstring(string str);
string wstring_to_string(wstring wstr);
// Initial Permutation Box before 16 round operation
int Initial_Permutation[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                               60, 52, 44, 36, 28, 20, 12, 4,
                               62, 54, 46, 38, 30, 22, 14, 6,
                               64, 56, 48, 40, 32, 24, 16, 8,
                               57, 49, 41, 33, 25, 17, 9, 1,
                               59, 51, 43, 35, 27, 19, 11, 3,
                               61, 53, 45, 37, 29, 21, 13, 5,
                               63, 55, 47, 39, 31, 23, 15, 7};

// Expand 32bit to 48bit (32bit of half left and half right 64bit block)
int Expansion_D_Box[48] = {32, 1, 2, 3, 4, 5,
                           4, 5, 6, 7, 8, 9,
                           8, 9, 10, 11, 12, 13,
                           12, 13, 14, 15, 16, 17,
                           16, 17, 18, 19, 20, 21,
                           20, 21, 22, 23, 24, 25,
                           24, 25, 26, 27, 28, 29,
                           28, 29, 30, 31, 32, 1};

// substitution box for each round ( total 16 box for 16 round operation)
int Substitution_Box[8][4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                                   0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                                   4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                                   15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                                  {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                                   3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                                   0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                                   13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

                                  {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                                   13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                                   13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                                   1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                                  {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                                   13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                                   10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                                   3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                                  {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                                   14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                                   4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                                   11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                                  {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                                   10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                                   9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                                   4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                                  {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                                   13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                                   1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                                   6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                                  {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                                   1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                                   7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                                   2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

// straight permutation box for 32 input and output 32 bit at last operation in Des function
int Straight_Permutaion_D_Box[32] = {16, 7, 20, 21,
                                     29, 12, 28, 17,
                                     1, 15, 23, 26,
                                     5, 18, 31, 10,
                                     2, 8, 24, 14,
                                     32, 27, 3, 9,
                                     19, 13, 30, 6,
                                     22, 11, 4, 25};

// final permutation box apply after 16 rounds
int Final_Permutation[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                             39, 7, 47, 15, 55, 23, 63, 31,
                             38, 6, 46, 14, 54, 22, 62, 30,
                             37, 5, 45, 13, 53, 21, 61, 29,
                             36, 4, 44, 12, 52, 20, 60, 28,
                             35, 3, 43, 11, 51, 19, 59, 27,
                             34, 2, 42, 10, 50, 18, 58, 26,
                             33, 1, 41, 9, 49, 17, 57, 25};

// Key party drop table is used to drop 8 bit to get 56 bit from key 64 bit
int Key_Party_Drop_Table[56] = {57, 49, 41, 33, 25, 17, 9,
                                1, 58, 50, 42, 34, 26, 18,
                                10, 2, 59, 51, 43, 35, 27,
                                19, 11, 3, 60, 52, 44, 36,
                                63, 55, 47, 39, 31, 23, 15,
                                7, 62, 54, 46, 38, 30, 22,
                                14, 6, 61, 53, 45, 37, 29,
                                21, 13, 5, 28, 20, 12, 4};

// shift table is number of shifts in each round key generations
int Shift_Table[16] = {1, 1, 2, 2,
                       2, 2, 2, 2,
                       1, 2, 2, 2,
                       2, 2, 2, 1};

// Key compression table is used to change the 58 bit key to 48 bit key
int Key_Compression_Table[48] = {14, 17, 11, 24, 1, 5,
                                 3, 28, 15, 6, 21, 10,
                                 23, 19, 12, 4, 26, 8,
                                 16, 7, 27, 20, 13, 2,
                                 41, 52, 31, 37, 47, 55,
                                 30, 40, 51, 45, 33, 48,
                                 44, 49, 39, 56, 34, 53,
                                 46, 42, 50, 36, 29, 32};
// Hex table is represent all character in hex format
string Hex_Table[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};

// convert the decimal number to binary number
string Decimal_to_Bin(int d, int length)
{
    string bin = "";
    if (d != 0)
    {
        while (d > 0)
        {
            bin = char('0' + d % 2) + bin;
            d /= 2;
        }
    }
    while (bin.length() < length)
    {
        bin = "0" + bin;
    }
    return bin;
}

// convert the binary number to decimal number
int Bin_to_Decimal(string bin)
{
    int d = 0;
    for (int i = 0; i < bin.length(); i++)
    {
        d += pow(2, bin.length() - 1 - i) * (bin[i] - '0');
    }
    return d;
}

//Get the hexadecimal value is represent in char
int getHexValue(char c)
{
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return c - '0';
    case 'A':
    case 'a':
        return 10;
    case 'B':
    case 'b':
        return 11;
    case 'C':
    case 'c':
        return 12;
    case 'D':
    case 'd':
        return 13;
    case 'E':
    case 'e':
        return 14;
    case 'F':
    case 'f':
        return 15;
    default:
        return -1;
    }
}

// Check all character in string is hexadecimal
bool Check_String_All_Hex(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (getHexValue(str[i]) == -1)
        {
            return false;
        }
    }
    return true;
}

// Convert Binary number to Hexadecimal number
string Bin_to_Hexadecimal(string Bin)
{
    string Bin_output = "";
    if (Bin.length() == 0)
    {
        return "0";
    }
    for (int i = 0; i < Bin.length() / 4; i++)
    {
        Bin_output += Hex_Table[Bin_to_Decimal(Bin.substr(i * 4, 4))];
    }
    return Bin_output;
}

// convert Hexadecimal number to binary
string Hexadecimal_to_Bin(string Hex)
{
    string Hex_ouput = "";
    for (int i = 0; i < Hex.length(); i++)
    {
        Hex_ouput += Decimal_to_Bin(getHexValue(Hex[i]), 4);
    }
    return Hex_ouput;
}

// convert ASCII (text) to hexadecimal number
string ASCII_to_Hexadecimal(string text)
{
    string bin = "";
    for (unsigned char c : text)
    {
        bin += Decimal_to_Bin(c, 8);
    }
    return Bin_to_Hexadecimal(bin);
}
// Convert hexadecimal number to ASCII(text)
string Hexadecimal_to_ASCII(string Hex)
{
    string Bin = Hexadecimal_to_Bin(Hex);
    string ASCII = "";
    for (long long i = 0; i < Bin.length() / 8; i++)
    {
        ASCII += (unsigned char)Bin_to_Decimal(Bin.substr(i * 8, 8));
    }
    return ASCII;
}

// permuataion operation with specifying table
// map the permutation box to the string
string Permute(string str, int *table, int n)
{
    string permute = "";
    for (int i = 0; i < n; i++)
    {
        permute += str[table[i] - 1];
    }
    return permute;
}

// shift string left to n_shifts bits
string Shift_Left(string str, int n_shifts)
{
    string sh_left = "";
    for (int i = 0; i < n_shifts; i++)
    {
        for (int j = 1; j < 28; j++)
        {
            sh_left += str[j];
        }
        sh_left += str[0];
        str = sh_left;
        sh_left = "";
    }
    return str;
}

// compute the bitwise xor str1 with str2
string Xor(string str1, string str2)
{
    string result = "";
    for (int i = 0; i < str1.length(); i++)
    {
        result += (char)(((str1[i] - '0') ^ (str2[i] - '0')) + '0');
    }

    return result;
}

// caculate the row value from bit 0 and bit 5 (in S-Box operation)
int Calculate_Row(string str)
{
    return 2 * (str[0] - '0') + (str[5] - '0');
}

// caculate the column value from bit 1 to bit 4 (in S-Box operation)
int Calculate_Column(string str)
{
    int result = 0;
    for (int i = 1; i < 5; i++)
    {
        result += pow(2, 4 - i) * (str[i] - '0');
    }
    return result;
}

// Swap tow string
void Swap(string &str1, string &str2)
{
    string temp = str1;
    str1 = str2;
    str2 = temp;
}

// DES operation can use either Encryption or Decryption operation
string Encrypt_Decrypt_64bit(string _text_64_bit, vector<string> round_key)
{
    // Initial Permutation
    _text_64_bit = Permute(_text_64_bit, Initial_Permutation, 64);

    // split 64 bit to 32bit left and 32 bit right
    string left = _text_64_bit.substr(0, 32);
    string right = _text_64_bit.substr(32, 32);

    for (int i = 0; i < 16; i++)
    {

        // Expand the 32bit right to 48 bit
        string right_expanded = Permute(right, Expansion_D_Box, 48);

        //xor round key with right_expanded
        string xor_right = Xor(round_key[i], right_expanded);

        // S boxes
        string output = "";

        // 8 S-boxes
        for (int i = 0; i < 8; i++)
        {
            // caculate row and column then map to the Substitution Box
            int row = Calculate_Row(xor_right.substr(i * 6, 6));
            int column = Calculate_Column(xor_right.substr(i * 6, 6));
            int math_S_table = Substitution_Box[i][row][column];

            // the ouput is convert to binary format
            output += Decimal_to_Bin(math_S_table, 4);
        }
        // straight Permutation D Box (32 bit input to 32 bit output)
        output = Permute(output, Straight_Permutaion_D_Box, 32);

        // Xor 32 bit left and output
        string left_xor = Xor(output, left);

        left = left_xor;

        // swap the left and right at the last operation except the final round(round 16)
        if (i != 15)
        {
            swap(left, right);
        }
    }
    // merger left and right string
    string merger = left + right;

    // Final Permutaition

    string cipher = Permute(merger, Final_Permutation, 64);
    return Bin_to_Hexadecimal(cipher);
}

// Generate random hexadecimal key with length 16
string GenerateKey()
{
    string key = "";
    for (int i = 0; i < 16; i++)
    {
        key += Hex_Table[rand() % 16];
    }
    return key;
}

// Caculate the round key from input key
vector<string> Generate_Round_Key(string key)
{
    vector<string> round_key;

    // Get 56 bit key from 64 bit key input by maping Key_Party_Drop_table
    key = Permute(key, Key_Party_Drop_Table, 56);

    // split key to 28bit left and 28bit right
    string left = key.substr(0, 28);
    string right = key.substr(28, 28);

    // caculate key for 16 round
    for (int i = 0; i < 16; i++)
    {
        // shift left key follow the Shift_Table
        left = Shift_Left(left, Shift_Table[i]);
        right = Shift_Left(right, Shift_Table[i]);

        // merger left and right
        string merger = left + right;

        // Compress key from 56 bit to 48 bit key
        string roundkey = Permute(merger, Key_Compression_Table, 48);
        round_key.push_back(roundkey);
    }
    return round_key;
}

class DES
{
private:
    string key;
    string iv;

public:
    // Default constructor
    DES()
    {
        // initial random seed
        srand(time(NULL));
        key = "";
        iv = "";
    }

    // Constructor
    DES(string key_input, string iv_input)
    {
        // initial random seed
        srand(time(NULL));
        Key_setter(key_input);
        Iv_setter(iv_input);
    }

    // Destructor
    ~DES()
    {
    }

    // Set the value for key
    bool Key_setter(string key_set)
    {
        if (key_set.length() != 16 || !Check_String_All_Hex(key_set))
        {
            wcout << "key set is invalid!" << endl;
            return false;
        }
        key = key_set;
        return true;
    }

    // Get the key value
    string Key_getter()
    {
        return key;
    }

    //Set the iv value for key
    bool Iv_setter(string iv_set)
    {
        if (iv_set.length() != 16 || !Check_String_All_Hex(iv_set))
        {
            wcout << "iv set is invalid!" << endl;
            return false;
        }
        iv = iv_set;
        return true;
    }

    string Iv_getter()
    {
        return iv;
    }
    //random the key
    void Auto_Generate_Key()
    {
        Key_setter(GenerateKey());
    }
    void Auto_Generate_IV()
    {
        Iv_setter(GenerateKey());
    }

    // Encyption operation
    string Encrypt(string plaintext)
    {

        // check key is valid
        if (key == "" || key.length() != 16)
        {
            wcout << "key is invalid!" << endl;
            exit(EXIT_FAILURE);
        }

        //check iv is valid
        if (iv == "" || iv.length() != 16)
        {
            wcout << "iv is invalid!" << endl;
            exit(EXIT_FAILURE);
        }

        // get length plaintext
        long long len_plaintext = plaintext.length();

        // padding null at the end with plaintext is divisible for 64 bit block size
        // Note: plaintext in ASCII format so has 8bit length for each character
        while ((len_plaintext * 8) % 64 != 0)
        {
            //padding null at the end
            plaintext = plaintext + char(0);
            len_plaintext = plaintext.length();
        }

        // convert plaintext to Hexadecimal format
        plaintext = ASCII_to_Hexadecimal(plaintext);

        string ciphertext = "";
        // Convert plaintext to Binary format
        plaintext = Hexadecimal_to_Bin(plaintext);
        wcout << "bin: " << string_to_wstring(plaintext) << endl;

        // compute the round key and stored in round_key
        vector<string> round_key = Generate_Round_Key(Hexadecimal_to_Bin(key));

        // reserved initial vector
        string iv_round = Hexadecimal_to_Bin(iv);
        //split the plain text into each 64bit block then encrypt
        for (long long i = 0; i < plaintext.length() / 64; i++)
        {
            string _text_64_bit = plaintext.substr(i * 64, 64);
            _text_64_bit = Xor(_text_64_bit, iv_round);

            // encrypt 64 bit and concatenate to the ciphertext
            string _64_bit_ciphertext;
            _64_bit_ciphertext = Encrypt_Decrypt_64bit(_text_64_bit, round_key);
            ciphertext += _64_bit_ciphertext;
            iv_round = Hexadecimal_to_Bin(_64_bit_ciphertext);
        }

        return ciphertext;
    }
    string Decrypt(string ciphertext)
    {
        string recovered_plaintext = "";

        // convert the Hexadecimal to binary format
        ciphertext = Hexadecimal_to_Bin(ciphertext);

        // compute the round_key from specific key
        vector<string> round_key = Generate_Round_Key(Hexadecimal_to_Bin(key));

        // Reverse round_key for decrypt operation
        reverse(round_key.begin(), round_key.end());

        string iv_round = Hexadecimal_to_Bin(iv);
        // split ciphertext into 64bit block then decrypt

        for (long long i = 0; i < ciphertext.length() / 64; i++)
        {
            string plaintext_64_bit = ciphertext.substr(i * 64, 64);
            // decrypt 64 bit and concatenate to the recoverd_plaintext
            string _64_bit_recovered = Hexadecimal_to_Bin(Encrypt_Decrypt_64bit(plaintext_64_bit, round_key));
            recovered_plaintext += Bin_to_Hexadecimal(Xor(iv_round, _64_bit_recovered));
            iv_round = plaintext_64_bit;
        }
        return recovered_plaintext;
    }
};
