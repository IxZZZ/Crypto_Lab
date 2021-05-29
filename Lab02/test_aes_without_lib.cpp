#include "AES_without_lib.h"
// library for unicode in C++
#include <fcntl.h> // _O_WTEXT
#include <io.h>    //_setmode()
#include <locale>
#include <codecvt>
using std::wstring;

// convert string to wstring (ASCII to utf8)
wstring string_to_wstring(string str)
{
     return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
}

// convert wstring(utf8) to string (ASCII)
string wstring_to_string(wstring wstr)
{
     return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);
}

// trim character rigth in string
string Trim_right(string str, char c)
{
     while (str[str.length() - 1] == c)
     {
          str.erase(str.length() - 1, 1);
     }
     return str;
}
int main()
{
     _setmode(_fileno(stdout), _O_WTEXT); // needed for output unicode
     _setmode(_fileno(stdin), _O_WTEXT);  // needed for input unicode

     wstring plaintext = L"Welcome the AES encryption and decryption!";
     AES aes;
     wcout
         << plaintext << endl;
     wcout << "[+] Input plaintext to encryption: ";
     fflush(stdin);
     getline(wcin, plaintext);

     wstring wkey;
     string key;
     wcout << endl;
     do
     {
          wcout << "[+] Enter key: ";
          fflush(stdin);
          getline(wcin, wkey);
          key = ASCII_to_Hexadecimal(wstring_to_string(wkey));

     } while (!aes.Key_setter(key));

     wstring wiv;
     string iv;
     wcout << endl;
     do
     {
          wcout << "[+] Enter iv: ";
          fflush(stdin);
          getline(wcin, wiv);
          iv = ASCII_to_Hexadecimal(wstring_to_string(wiv));

     } while (!aes.Iv_setter(iv));

     wcout << endl;
     wcout << "Key(hex): " << string_to_wstring(aes.Key_getter()) << endl
           << endl;
     wcout << "Iv(hex): " << string_to_wstring(aes.Iv_getter()) << endl
           << endl;
     wcout << "Plaintext(utf8): " << plaintext << endl
           << endl;

     wcout << "\n-----Encryption-----\n";
     wcout << "Plaintext (hex): " << string_to_wstring(ASCII_to_Hexadecimal(wstring_to_string(plaintext))) << endl
           << endl;
     string ciphertext = aes.Encryption(wstring_to_string(plaintext));

     wcout << "Ciphertext (hex): " << string_to_wstring(ciphertext) << endl
           << endl;
     wcout << "\n-----Decryption-----\n";
     wcout << "Ciphertext (hex): " << string_to_wstring(ciphertext) << endl
           << endl;
     string encrypted = aes.Decryption(ciphertext);
     wcout << "Recovered (hex): " << string_to_wstring(encrypted) << endl
           << endl;
     wcout << "Recorvered ciphertext(utf8): " << string_to_wstring(Hexadecimal_to_ASCII(encrypted)) << endl;

     return 0;
}
//test->  Input iterators to the initial and final positions in a range. The range used is [first,last), which includes all the characters between first and last, including the character pointed by first but not the character pointed by last.The function template argument InputIterator shall be an input iterator type that points to elements of a type convertible to char.
