#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <bitset>

using namespace std;
wstring string_to_wstring(string str);
string wstring_to_string(wstring wstr);
//Substitution box for encryption and key expansion
int Substitution_Box[16][16] = {{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
                                {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
                                {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
                                {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
                                {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
                                {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
                                {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
                                {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
                                {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
                                {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
                                {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
                                {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
                                {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
                                {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
                                {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
                                {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

// inverse substitution box for decryption
int Substitution_Box_Inverse[16][16] = {{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
                                        {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
                                        {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
                                        {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
                                        {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
                                        {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
                                        {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
                                        {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
                                        {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
                                        {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
                                        {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
                                        {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
                                        {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
                                        {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
                                        {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
                                        {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};

// Galois Field multiplication matrix for encryption
const int GF_Multiplication_Matrix[4][4] = {{0x2, 0x3, 0x1, 0x1},
                                            {0x1, 0x2, 0x3, 0x1},
                                            {0x1, 0x1, 0x2, 0x3},
                                            {0x3, 0x1, 0x1, 0x2}};

// Inverse Galois Field multiplication matrix for decryption
const int GF_Multiplication_Inverse_Matrix[4][4] = {{0xe, 0xb, 0xd, 0x9},
                                                    {0x9, 0xe, 0xb, 0xd},
                                                    {0xd, 0x9, 0xe, 0xb},
                                                    {0xb, 0xd, 0x9, 0xe}};
// polynominal x^8 + x^4 + x^3 + x + 1
const string GF256_Polynominal = "100011011";

// const int n_rounds = 10;
// const int n_k_words = 4;
// const int n_b_words = 4;

// constant round key
const string constant_rounds_key[10] = {"01000000",
                                        "02000000",
                                        "04000000",
                                        "08000000",
                                        "10000000",
                                        "20000000",
                                        "40000000",
                                        "80000000",
                                        "1b000000",
                                        "36000000"};

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

// Hex table is represent all character in hex format
string Hex_Table[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};

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
        int c = Bin_to_Decimal(Bin.substr(i * 8, 8));
        ASCII += (char)c;
    }
    return ASCII;
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

// shift string left to n_shifts bits
string Shift_Left(string str, int n_shifts)
{
    string sh_left = "";
    for (int i = 0; i < n_shifts; i++)
    {
        for (int j = 1; j < 32; j++)
        {
            sh_left += str[j];
        }
        sh_left += str[0];
        str = sh_left;
        sh_left = "";
    }
    return str;
}

// shift string right to n_shifts bits
string Shift_Right(string str, int n_shifts)
{
    string sh_right = "";
    for (int i = 0; i < n_shifts; i++)
    {
        for (int j = 0; j < 31; j++)
        {
            sh_right += str[j];
        }
        sh_right = str[31] + sh_right;
        str = sh_right;
        sh_right = "";
    }
    return str;
}

// Substitution 32bit word
string Substitution_Word(string word, bool is_inverse)
{
    string temp;
    for (int i = 0; i < 32; i += 8)
    {
        //split 4 bits left for row
        string row_str = word.substr(i, 4);
        int row = Bin_to_Decimal(row_str);

        // split 4 bits right for column
        string column_str = word.substr(i + 4, 4);
        int column = Bin_to_Decimal(column_str);

        int map_box;

        // Inverse Substitution for decryption
        if (is_inverse)
        {
            map_box = Substitution_Box_Inverse[row][column];
        }
        // Substitution for encryption
        else
        {
            map_box = Substitution_Box[row][column];
        }
        temp += Decimal_to_Bin(map_box, 8);
    }
    return temp;
}

// Compute Key expansion for each round
void Key_Expansion(string key, string Key_Expanded[10])
{
    int i = 0;
    // Convert key to binary
    key = Hexadecimal_to_Bin(key);

    // loop for 10 rounds key
    while (i < 10)
    {
        // get last column to preprocess key
        string Last_column = key.substr(32 * 3, 32);

        // shift left last column
        string shift_left = Shift_Left(Last_column, 8);

        // Substitution for last column
        string Substitution = Substitution_Word(shift_left, 0);

        // xor last column with constant rounds key
        string Xor_constant_round = Xor(Substitution, Hexadecimal_to_Bin(constant_rounds_key[i]));

        // xor each columns with Xor_constant_column
        for (int j = 0; j < 4; j++)
        {
            // xor previous column with current column
            Xor_constant_round = Xor(key.substr(j * 32, 32), Xor_constant_round);

            // store in Key_Expanded
            Key_Expanded[i] += Xor_constant_round;
        }
        // use the new key round for next key_expand operation
        key = Key_Expanded[i];
        i++;
    }
}

// Read the string with vertically direction
string Read_Vertically(string text_128)
{
    string vertically_string = "";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            vertically_string += text_128.substr(32 * j + i * 8, 8);
        }
    }
    return vertically_string;
}

//Substitution string 128 bits length for encryption and decryption
// is_inverse = 0 -> encryption
// is_inverse = 1 -> decryption
string Sub_Bytes(string plain_128, bool is_inverse)
{
    string Substitution = "";
    for (int i = 0; i < 4; i++)
    {
        Substitution += Substitution_Word(plain_128.substr(i * 32, 32), is_inverse);
    }
    return Substitution;
}

// shift the row left n*8 bits with n is row index (is used for encryption)
string Shift_Row_Left(string plain_128)
{
    string shift = "";
    for (int i = 0; i < 4; i++)
    {
        // shift each row 32 bits
        shift += Shift_Left(plain_128.substr(i * 32, 32), i * 8);
    }

    return shift;
}

// shift the row right n*8 bits with n is row index (is used for decryption)
string Shift_Row_Right(string plain_128)
{
    string shift = "";

    for (int i = 0; i < 4; i++)
    {
        // shift each row with 32 bits
        string sh = Shift_Right(plain_128.substr(i * 32, 32), i * 8);
        shift += sh;
    }

    return shift;
}

// multiplication GF polynominal
string Mul_polynominal(string a, string b)
{
    // n is the max degree of multiplication result
    const int n = a.length() + b.length();

    string result = "";

    //set 8 bits 0 for result
    for (int i = 0; i < n - 1; i++)
    {
        result += '0';
    }

    // implementation multiplication and modulous 2
    for (int i = 0; i < a.length(); i++)
    {
        for (int j = 0; j < b.length(); j++)
        {
            result[i + j] = (char)(((result[i + j] - '0') + (a[i] - '0') * (b[j] - '0')) % 2 + '0');
        }
    }
    return result;
}

// caculate multiplication Galosi Field 2^8 bit
string GF_256_Mul(string a, string b)
{
    // compute multiplication polynominal
    string result = Mul_polynominal(a, b);

    // Modulous to polynominal x^8 + x^4 + x^3 + x + 1 by xor algorithm
    int i = 0;
    // Get the first bit 1 poition
    for (i = 0; i < 7; i++)
    {
        if (result[i] == '1')
        {
            break;
        }
    }
    // if result multiplication > x^8 + x^4 + x^3 + x + 1
    if (i < 7)
    {
        // Implemetation Xor to get the remainder
        while (i + 8 <= 14)
        {
            result = result.substr(0, i) + Xor(result.substr(i, 9), GF256_Polynominal) + result.substr(i + 9, 32 - 9 - i);

            while (result[i] != '1' && i < 14)
            {
                i++;
            }
        }
    }

    // strip front to get 8 bits length
    while (result.length() > 8)
    {
        result.replace(0, 1, "");
    }

    return result;
}

// Mi columsn operation
// is_inverse = 0 -> encryption
// is_inverse = 1 -> decryption
string Mix_Columns(string plain_128, bool is_inverse)
{
    // read the plaintext vertically direction
    plain_128 = Read_Vertically(plain_128);

    // result of Mix columsn operations
    string Mix = "";
    // 4 loop i for 32bit columns
    for (int i = 0; i < 4; i++)
    {
        // get column by column
        string column = plain_128.substr(32 * i, 32);

        // 4 loop j for GF_Multiplication_Matrix row
        for (int j = 0; j < 4; j++)
        {
            string result = "00000000";
            // 4 loop k for GF_multiplication_Matrix column and each 8 bits of column
            for (int k = 0; k < 4; k++)
            {
                if (is_inverse)
                {
                    // inverse for decryption
                    // compute inverse multiplication GF 2^8 and xor with result then store to result
                    result = Xor(GF_256_Mul(column.substr(k * 8, 8), Decimal_to_Bin(GF_Multiplication_Inverse_Matrix[j][k], 8)), result);
                }
                else
                {
                    // for encryption
                    // compute multiplication GF 2^8 and xor with result then store to result
                    result = Xor(GF_256_Mul(column.substr(k * 8, 8), Decimal_to_Bin(GF_Multiplication_Matrix[j][k], 8)), result);
                }
            }

            Mix += result;
        }
    }

    return Read_Vertically(Mix);
}

// Xor each 8 bits of str1 and str2 follow row by row
string Xor_row_by_row(string str1, string str2)
{
    string xor_res = "";
    for (int i = 0; i < 16; i++)
    {
        xor_res += Xor(str1.substr(i * 8, 8), str2.substr(i * 8, 8));
    }
    return xor_res;
}

// Encrypt 128 bit length
string Encrypt_128(string plain_128, string key)
{
    string Key_Expanded[10];

    // compute the key_expanded from specific key
    Key_Expansion(key, Key_Expanded);

    int rounds = 0;
    // convert key to binary
    key = Hexadecimal_to_Bin(key);

    // Add keys operation
    plain_128 = Xor_row_by_row(Read_Vertically(plain_128), Read_Vertically(key));

    string cipher_128 = plain_128;

    //loop for 10 rounds
    while (rounds < 10)
    {
        // Substitiontion 128 bits length operation
        cipher_128 = Sub_Bytes(cipher_128, 0);

        // Shift row operation
        cipher_128 = Shift_Row_Left(cipher_128);

        // Mix columns opeation except the tenth round (the last round)
        if (rounds != 9)
        {
            cipher_128 = Mix_Columns(cipher_128, 0);
        }

        // Add keys operation and store cipher to use for the next round
        cipher_128 = Xor_row_by_row(cipher_128, Read_Vertically(Key_Expanded[rounds]));

        rounds++;
    }

    return Read_Vertically(cipher_128);
}

// Decrypt 128 bits length
string Decrypt_128(string cipher_128, string key)
{
    string Key_Expanded[10];

    // compute key_expanded from specific key
    Key_Expansion(key, Key_Expanded);

    // 10 rouds for AES oepration
    int rounds = 10;

    // convert key to binary
    key = Hexadecimal_to_Bin(key);

    string plain_128 = Read_Vertically(cipher_128);

    // loop inverse 10 round for decryption
    // the operation step is inverse with decryption operation step
    while (rounds > 0)
    {
        // Addes key operation
        plain_128 = Xor_row_by_row(plain_128, Read_Vertically(Key_Expanded[rounds - 1]));

        // Mix columns except the tenth round
        if (rounds != 10)
        {
            plain_128 = Mix_Columns(plain_128, 1);
        }

        // shift rows operation
        plain_128 = Shift_Row_Right(plain_128);

        // Substitution 128 bits length operation
        plain_128 = Sub_Bytes(plain_128, 1);

        rounds--;
    }
    plain_128 = Xor_row_by_row(Read_Vertically(plain_128), key);
    return plain_128;
}

// Random 32 bit hexadecimal key
string GenerateKey()
{
    string key = "";

    for (int i = 0; i < 32; i++)
    {
        key += Hex_Table[rand() % 16];
    }
    return key;
}

class AES
{
private:
    string key;
    string iv;

public:
    // Default constructor
    AES()
    {
        srand(time(NULL));
        key = "";
        iv = "";
    }

    // Destructor
    ~AES()
    {
    }

    // Constructor
    AES(string key_input, string iv_input)
    {
        srand(time(NULL));
        Key_setter(key_input);
        Iv_setter(iv_input);
    }

    // Auto generate key
    void Auto_Generate_Key()
    {
        Key_setter(GenerateKey());
    }

    void Auto_Generate_Iv()
    {
        Iv_setter(GenerateKey());
    }
    // set the value for key in hexadecimal
    bool Key_setter(string key_input)
    {
        if (key_input.length() != 32 || !Check_String_All_Hex(key_input))
        {
            wcout << "Key input is invalid!" << endl;
            return false;
        }

        key = key_input;
        return true;
    }

    // get the value of key
    string Key_getter()
    {
        return key;
    }

    // set the value for key in hexadecimal
    bool Iv_setter(string iv_input)
    {
        if (iv_input.length() != 32 || !Check_String_All_Hex(iv_input))
        {
            wcout << "Iv input is invalid!" << endl;
            return false;
        }

        iv = iv_input;
        return true;
    }

    // get the value of iv
    string Iv_getter()
    {
        return iv;
    }

    // Encryption full plaintext
    string Encryption(string plaintext)
    {
        // check key is valid
        if (key == "" || key.length() != 32)
        {
            wcout << "key is invalid!" << endl;
            exit(EXIT_FAILURE);
        }
        // check iv is valid
        if (iv == "" || iv.length() != 32)
        {
            wcout << "iv is invalid!" << endl;
            exit(EXIT_FAILURE);
        }

        // get key length
        long long len_plaintext = plaintext.length();

        // plaintext in ASCII so it is 8 bits length
        while ((len_plaintext * 8) % 128 != 0)
        {
            //padding in front of with null
            plaintext = plaintext + char(0);
            len_plaintext = plaintext.length();
        }

        // Convert plaintext to hexadecimal
        plaintext = ASCII_to_Hexadecimal(plaintext);

        string ciphertext = "";

        // convert plaintext to binary
        plaintext = Hexadecimal_to_Bin(plaintext);

        // reserved iv
        string iv_round = Hexadecimal_to_Bin(iv);
        // Split plaintext into each 128 bits length the encrypt
        for (long long i = 0; i < plaintext.length() / 128; i++)
        {
            string _text_128_bit = plaintext.substr(i * 128, 128);
            _text_128_bit = Xor(_text_128_bit, iv_round);
            // Encrypt 128 bits length the Concatenate to ciphertext
            string _128_bit_ciphertext;
            _128_bit_ciphertext = Encrypt_128(_text_128_bit, key);
            ciphertext += _128_bit_ciphertext;
            iv_round = _128_bit_ciphertext;
        }

        // return ciphertext in hexadecimal format
        return Bin_to_Hexadecimal(ciphertext);
    }

    // Decryption full ciphertext
    string Decryption(string ciphertext)
    {
        // check key is valid
        if (key == "" || key.length() != 32)
        {
            wcout << "Key is invalid!" << endl;
            exit(EXIT_FAILURE);
        }

        string recovered_plaintext = "";

        // convert ciphertext to binary
        ciphertext = Hexadecimal_to_Bin(ciphertext);

        // reserved iv
        string iv_round = Hexadecimal_to_Bin(iv);

        // split ciphertext into each 128 bits length then decrypt
        for (long long i = 0; i < ciphertext.length() / 128; i++)
        {
            string plaintext_64_bit = ciphertext.substr(i * 128, 128);
            // decrypt 128 bits length the concatenate to recorverd_plaintext
            string _64_bit_recovered = Decrypt_128(plaintext_64_bit, key);
            recovered_plaintext += Xor(_64_bit_recovered, iv_round);
            iv_round = plaintext_64_bit;
        }

        // return recovered_plaintext in Hexadecimal format
        return Bin_to_Hexadecimal(recovered_plaintext);
    }
};
