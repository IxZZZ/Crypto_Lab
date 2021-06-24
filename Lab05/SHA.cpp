#include <iostream>
#include <iostream>
using std::cerr;
using std::endl;
using std::string;
using std::wcin;
using std::wcout;
using std::wstring;

/* Vietnamese support */

/* Set _setmode()*/
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else

#ifdef __linux__
__fpurge(stdin);
#elif _WIN32
fflush(stdin);
#else
#endif

#endif

/* String convert */
#include <locale>
using std::wstring_convert;
#include <codecvt>
using std::codecvt_utf8;

#include "cryptopp/sha.h"
using CryptoPP::SHA224;
using CryptoPP::SHA256;
using CryptoPP::SHA384;
using CryptoPP::SHA512;

#include "cryptopp/sha3.h"
using CryptoPP::SHA3_224;
using CryptoPP::SHA3_256;
using CryptoPP::SHA3_384;
using CryptoPP::SHA3_512;

#include "cryptopp/shake.h"
using CryptoPP::SHAKE128;
using CryptoPP::SHAKE256;

#include "cryptopp/cryptlib.h"
using CryptoPP::DecodingResult;
using CryptoPP::Exception;

#include "cryptopp/filters.h"
using CryptoPP::HashFilter;
using CryptoPP::Redirector;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

//#include"cryptopp/buffrt
using namespace std;

/* Vietnames convert function def*/
/* convert string to wstring */
wstring string_to_wstring(const std::string &str)
{
    wstring_convert<codecvt_utf8<wchar_t>> towstring;
    return towstring.from_bytes(str);
}

/* convert wstring to string */
string wstring_to_string(const std::wstring &str)
{
    wstring_convert<codecvt_utf8<wchar_t>> tostring;
    return tostring.to_bytes(str);
}

template <typename T>
void Hash(string msg)
{
    T hash;

    wcout << "Name: " << string_to_wstring(hash.AlgorithmName()) << endl;
    wcout << "Digest size: " << hash.DigestSize() << endl;
    wcout << "Block size: " << hash.BlockSize() << endl;

    string digest;
    int loop = 10000;
    int start_s = clock();
    while (loop--)
    {
        digest.clear();
        StringSource(msg, true, new HashFilter(hash, new StringSink(digest))); // StringSource
    }
    int stop_s = clock();
    double etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

    wcout << "Message: " << string_to_wstring(msg) << endl;
    wcout << "Digest: " << endl;

    string hash_result;
    StringSource(digest, true, new HexEncoder(new StringSink(hash_result)));

    wcout << string_to_wstring(hash_result) << endl;
    wcout << endl;
    wcout << "[+] Performance\n";
    wcout << "Total execution time for 10.000 loop: " << etime << "ms\n";
    wcout << "Average execution time: " << etime / 10000 << "ms" << endl;
}

template <typename T>
void Hash_Shake(string msg)
{
    T hash;
    while (1)
    {
        wcout << endl;
        wcout << "Enter output length for SHAKE: ";
        int size;
        wcin >> size;
        if (size > 0)
        {
            T shake(size);
            hash = shake;
            break;
        }
        wcout << endl;
        wcout << "Invalid Input!!\n";
    }
    wcout << "Name: " << string_to_wstring(hash.AlgorithmName()) << endl;
    wcout << "Digest size: " << hash.DigestSize() << endl;
    wcout << "Block size: " << hash.BlockSize() << endl;

    string digest;
    int loop = 10000;
    int start_s = clock();
    while (loop--)
    {
        digest.clear();
        StringSource(msg, true, new HashFilter(hash, new StringSink(digest))); // StringSource
    }
    int stop_s = clock();
    double etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

    wcout << "Message: " << string_to_wstring(msg) << endl;
    wcout << "Digest: " << endl;

    string hash_result;
    StringSource(digest, true, new HexEncoder(new StringSink(hash_result)));

    wcout << string_to_wstring(hash_result) << endl;
    wcout << endl;
    wcout << "[+] Performance\n";
    wcout << "Total execution time for 10.000 loop: " << etime << "ms\n";
    wcout << "Average execution time: " << etime / 10000 << "ms" << endl;
}

int main()
{
    /*Set mode support Vietnamese*/
#ifdef __linux__
    setlocale(LC_ALL, "");
#elif _WIN32
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
#else
#endif

    wcout << "~~ Welcome to hash algorithm ~~";

    int options_algo;
    while (1)
    {
        wcout << endl;
        wcout << "[+] Hash Algorithm Selection: " << endl;
        wcout << "[1] SHA224\n";
        wcout << "[2] SHA256\n";
        wcout << "[3] SHA384\n";
        wcout << "[4] SHA512\n";
        wcout << "[5] SHA3-224\n";
        wcout << "[6] SHA3-256\n";
        wcout << "[7] SHA3-384\n";
        wcout << "[8] SHA3-512\n";
        wcout << "[9] SHAKE128\n";
        wcout << "[10] SHAKE256\n";
        wcout << "Enter option: ";
        wcin >> options_algo;
        if (options_algo >= 1 && options_algo <= 10)
        {
            break;
        }
        wcout << endl;
        wcout << "Invalid options!!\n";
    }

    int options_input;
    while (1)
    {
        wcout << endl;
        wcout << "[+] Input message\n";
        wcout << "[1] Input from key board\n";
        wcout << "[2] Input from file\n";
        wcout << "Enter option: ";
        wcin >> options_input;
        if (options_input == 1 || options_input == 2)
        {
            break;
        }
        wcout << endl;
        wcout << "Invalid Options" << endl;
    }

    wstring w_input;
    string msg;
    if (options_input == 1)
    {
        wcout << endl;
        wcout << "Enter message: ";

#ifdef __linux__
        __fpurge(stdin);
#elif _WIN32
        fflush(stdin);
#else
#endif

        getline(wcin, w_input);
        msg = wstring_to_string(w_input);
    }
    else
    {
        wcout << endl;
        wcout << "Enter filename: ";

#ifdef __linux__
        __fpurge(stdin);
#elif _WIN32
        fflush(stdin);
#else
#endif

        getline(wcin, w_input);
        string filename = wstring_to_string(w_input);
        FileSource file_to_str((const char *)(filename.data()), true, new StringSink(msg));
    }

    switch (options_algo)
    {
    case 1:
        Hash<SHA224>(msg);
        break;
    case 2:
        Hash<SHA256>(msg);
        break;
    case 3:
        Hash<SHA384>(msg);
        break;
    case 4:
        Hash<SHA512>(msg);
        break;
    case 5:
        Hash<SHA3_224>(msg);
        break;
    case 6:
        Hash<SHA3_256>(msg);
        break;
    case 7:
        Hash<SHA3_384>(msg);
        break;
    case 8:
        Hash<SHA3_512>(msg);
        break;
    case 9:
        Hash_Shake<SHAKE128>(msg);
        break;
    case 10:
        Hash_Shake<SHAKE256>(msg);
        break;
    }

    return 0;
}