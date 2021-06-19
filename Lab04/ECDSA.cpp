// ECDSA.KeyGen.cpp : Defines the entry point for the console application.
//

#include <assert.h>
#include <ctime>
#include <stdio.h>
#include <iostream>
using std::endl;
using std::wcout;

#include <string>
using std::string;

#include "cryptopp/osrng.h"
// using CryptoPP::AutoSeededX917RNG;
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/aes.h"
using CryptoPP::AES;

#include "cryptopp/integer.h"
using CryptoPP::Integer;

#include "cryptopp/sha.h"
using CryptoPP::SHA1;

/* Convert to hex */
#include <cryptopp/hex.h>
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "cryptopp/filters.h"
using CryptoPP::ArraySink;
using CryptoPP::SignatureVerificationFilter;
using CryptoPP::SignerFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/eccrypto.h"
using CryptoPP::DL_GroupParameters_EC;
using CryptoPP::ECDSA;
using CryptoPP::ECP;

#include "cryptopp/oids.h"
using CryptoPP::byte;
using CryptoPP::OID;

/* Vietnamese support */

/* Set _setmode()*/
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else
#include <stdio_ext.h> // _fpurge(stdin) == fflush(stdin)
#endif

/* String convert */
#include <locale>
using std::wstring_convert;
#include <codecvt>
using std::codecvt_utf8;

#include <fstream>

using std::cerr;
using std::endl;
using std::wcin;
using std::wcout;
using std::wstring;

/* Integer convert */
#include <sstream>
using std::ostringstream;

bool GeneratePrivateKey(const OID &oid, ECDSA<ECP, SHA1>::PrivateKey &key);
bool GeneratePublicKey(const ECDSA<ECP, SHA1>::PrivateKey &privateKey, ECDSA<ECP, SHA1>::PublicKey &publicKey);

void SavePrivateKey(const string &filename, const ECDSA<ECP, SHA1>::PrivateKey &key);
void SavePublicKey(const string &filename, const ECDSA<ECP, SHA1>::PublicKey &key);
void LoadPrivateKey(const string &filename, ECDSA<ECP, SHA1>::PrivateKey &key);
void LoadPublicKey(const string &filename, ECDSA<ECP, SHA1>::PublicKey &key);

void PrintDomainParameters(const ECDSA<ECP, SHA1>::PrivateKey &key);
void PrintDomainParameters(const ECDSA<ECP, SHA1>::PublicKey &key);
void PrintDomainParameters(const DL_GroupParameters_EC<ECP> &params);
void PrintPrivateKey(const ECDSA<ECP, SHA1>::PrivateKey &key);
void PrintPublicKey(const ECDSA<ECP, SHA1>::PublicKey &key);

bool SignMessage(const ECDSA<ECP, SHA1>::PrivateKey &key, const string &message, string &signature);
bool VerifyMessage(const ECDSA<ECP, SHA1>::PublicKey &key, const string &message, const string &signature);

/* Vietnames convert function def*/
wstring string_to_wstring(const std::string &str);
string wstring_to_string(const std::wstring &str);
wstring integer_to_wstring(const CryptoPP::Integer &t);
string wstring_hex_to_string(wstring wstr);

// Signing and verifying funciton
void Sign();
void Verify();

// Input Messgase and signature for sign and verify

string Input_Message();
string Input_Signature();

// Input key
void Input_PrivateKey(ECDSA<ECP, SHA1>::PrivateKey &key);
void Input_PublicKey(ECDSA<ECP, SHA1>::PublicKey &key);

int main(int argc, char *argv[])
{
    /*Set mode support Vietnamese*/
#ifdef __linux__
    setlocale(LC_ALL, "");
#elif _WIN32
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
#else
#endif

    try
    {
        do
        {
            wcout << endl;
            wcout << "~Welcome the Elliptic Curve Digital Signature Algorithm~\n"
                  << endl;
            wcout << "[1] Sign message with private key\n";
            wcout << "[2] Verify message with public key\n";
            wcout << "[3] Exit.\n";
            wcout << "Enter option: ";
            int option;
            wcin >> option;
            if (option == 1)
            {
                Sign();
            }
            else if (option == 2)
            {
                Verify();
            }
            else if (option == 3)
            {
                break;
            }
            else
            {
                wcout << "Invalid Option!" << endl;
            }
        } while (1);
    }
    catch (CryptoPP::Exception &e)
    {
        cerr << "Caught Exception..." << endl;
        cerr << e.what() << endl;
    }

    return 0;
}

bool GeneratePrivateKey(const OID &oid, CryptoPP::ECDSA<ECP, SHA1>::PrivateKey &key)
{
    AutoSeededRandomPool prng;

    key.Initialize(prng, oid);
    assert(key.Validate(prng, 3));

    return key.Validate(prng, 3);
}

bool GeneratePublicKey(const CryptoPP::ECDSA<ECP, SHA1>::PrivateKey &privateKey, CryptoPP::ECDSA<ECP, SHA1>::PublicKey &publicKey)
{
    AutoSeededRandomPool prng;

    // Sanity check
    assert(privateKey.Validate(prng, 3));

    privateKey.MakePublicKey(publicKey);
    assert(publicKey.Validate(prng, 3));

    return publicKey.Validate(prng, 3);
}

void PrintDomainParameters(const CryptoPP::ECDSA<ECP, SHA1>::PrivateKey &key)
{
    PrintDomainParameters(key.GetGroupParameters());
}

void PrintDomainParameters(const CryptoPP::ECDSA<ECP, SHA1>::PublicKey &key)
{
    PrintDomainParameters(key.GetGroupParameters());
}

void PrintDomainParameters(const CryptoPP::DL_GroupParameters_EC<ECP> &params)
{
    wcout << endl;

    wcout << "Modulus:" << endl;
    wcout << " " << integer_to_wstring(params.GetCurve().GetField().GetModulus()) << endl;

    wcout << "Coefficient A:" << endl;
    wcout << " " << integer_to_wstring(params.GetCurve().GetA()) << endl;

    wcout << "Coefficient B:" << endl;
    wcout << " " << integer_to_wstring(params.GetCurve().GetB()) << endl;

    wcout << "Base Point:" << endl;
    wcout << " X: " << integer_to_wstring(params.GetSubgroupGenerator().x) << endl;
    wcout << " Y: " << integer_to_wstring(params.GetSubgroupGenerator().y) << endl;

    wcout << "Subgroup Order:" << endl;
    wcout << " " << integer_to_wstring(params.GetSubgroupOrder()) << endl;

    wcout << "Cofactor:" << endl;
    wcout << " " << integer_to_wstring(params.GetCofactor()) << endl;
}

void PrintPrivateKey(const CryptoPP::ECDSA<ECP, SHA1>::PrivateKey &key)
{
    wcout << endl;
    wcout << "Private Exponent:" << endl;
    wcout << " " << integer_to_wstring(key.GetPrivateExponent()) << endl;
}

void PrintPublicKey(const CryptoPP::ECDSA<ECP, SHA1>::PublicKey &key)
{
    wcout << endl;
    wcout << "Public Element:" << endl;
    wcout << " X: " << integer_to_wstring(key.GetPublicElement().x) << endl;
    wcout << " Y: " << integer_to_wstring(key.GetPublicElement().y) << endl;
}

void SavePrivateKey(const string &filename, const CryptoPP::ECDSA<ECP, SHA1>::PrivateKey &key)
{
    key.Save(FileSink(filename.c_str(), true /*binary*/).Ref());
}

void SavePublicKey(const string &filename, const CryptoPP::ECDSA<ECP, SHA1>::PublicKey &key)
{
    key.Save(FileSink(filename.c_str(), true /*binary*/).Ref());
}

void LoadPrivateKey(const string &filename, CryptoPP::ECDSA<ECP, SHA1>::PrivateKey &key)
{
    key.Load(FileSource(filename.c_str(), true /*pump all*/).Ref());
}

void LoadPublicKey(const string &filename, CryptoPP::ECDSA<ECP, SHA1>::PublicKey &key)
{
    key.Load(FileSource(filename.c_str(), true /*pump all*/).Ref());
}

bool SignMessage(const CryptoPP::ECDSA<ECP, SHA1>::PrivateKey &key, const string &message, string &signature)
{
    AutoSeededRandomPool prng;

    signature.erase();

    StringSource(message, true,
                 new SignerFilter(prng,
                                  CryptoPP::ECDSA<ECP, SHA1>::Signer(key),
                                  new StringSink(signature)) // SignerFilter
    );                                                       // StringSource

    return !signature.empty();
}

bool VerifyMessage(const CryptoPP::ECDSA<ECP, SHA1>::PublicKey &key, const string &message, const string &signature)
{
    bool result = false;

    StringSource(signature + message, true,
                 new SignatureVerificationFilter(
                     CryptoPP::ECDSA<ECP, SHA1>::Verifier(key),
                     new ArraySink((byte *)&result, sizeof(result))) // SignatureVerificationFilter
    );

    return result;
}

/* Convert interger to wstring */
wstring integer_to_wstring(const CryptoPP::Integer &t)
{
    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << t;                       // pumb t to oss
    std::string encoded(oss.str()); // to string
    std::wstring_convert<codecvt_utf8<wchar_t>> towstring;
    return towstring.from_bytes(encoded); // string to wstring
}

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

/* convert wstring hex to string */
string wstring_hex_to_string(wstring wstr)
{
    string str;
    StringSource(wstring_to_string(wstr), true, new HexDecoder(new StringSink(str)));
    return str;
}

string Input_Message()
{
    do
    {
        wcout << endl;
        wcout << "[+] Input Message\n";
        wcout << "[1] Message from file\n";
        wcout << "[2] Message from key board\n";
        wcout << "Enter option: ";
        int option;
        wcin >> option;
        if (option == 1)
        {
            wcout << "Enter file name: ";
            wstring filename;

#ifdef __linux__
            __fpurge(stdin);
#elif _WIN32
            fflush(stdin);
#else
#endif

            getline(wcin, filename);
            std::ifstream file;
            file.open((wstring_to_string(filename)));
            if (!file.is_open())
            {
                wcout << "Can not open file!\n";
                continue;
            }
            string message;

#ifdef __linux__
            __fpurge(stdin);
#elif _WIN32
            fflush(stdin);
#else
#endif

            getline(file, message);
            return message;
        }
        else if (option == 2)
        {
            wstring message;
            wcout << "Enter Message: ";

#ifdef __linux__
            __fpurge(stdin);
#elif _WIN32
            fflush(stdin);
#else
#endif

            getline(wcin, message);
            return wstring_to_string(message);
        }
        else
        {
            wcout << "Invalid Option!" << endl;
        }

    } while (1);
}

string Input_Signature()
{
    do
    {
        wcout << endl;
        wcout << "[+] Input Signature\n";
        wcout << "[1] Signature from file\n";
        wcout << "[2] Signature from key board\n";
        wcout << "Enter option: ";
        int option;
        wcin >> option;
        if (option == 1)
        {
            wcout << "Enter file name: ";
            wstring filename;

#ifdef __linux__
            __fpurge(stdin);
#elif _WIN32
            fflush(stdin);
#else
#endif

            getline(wcin, filename);
            std::ifstream file;
            file.open((wstring_to_string(filename)));
            if (file.is_open() == false)
            {
                wcout << "Can not open file!\n";
                continue;
            }
            string signature;

#ifdef __linux__
            __fpurge(stdin);
#elif _WIN32
            fflush(stdin);
#else
#endif

            getline(file, signature);
            return signature;
        }
        else if (option == 2)
        {
            wstring signature;
            wcout << "Enter Signature: ";

#ifdef __linux__
            __fpurge(stdin);
#elif _WIN32
            fflush(stdin);
#else
#endif

            getline(wcin, signature);
            return wstring_hex_to_string(signature);
        }
        else
        {
            wcout << "Invalid Option!" << endl;
        }

    } while (1);
}

void Sign()
{
    string message, signature;

    // private key for signing
    CryptoPP::ECDSA<ECP, SHA1>::PrivateKey privateKey;

    wcout << endl;
    wcout << "[+] Signing\n";
    message = Input_Message();

    Input_PrivateKey(privateKey);

    wcout << endl;
    wcout << "Message: " << string_to_wstring(message) << endl;

    PrintPrivateKey(privateKey);

    string hex_signature;

    int loop = 10000;
    bool result;
    int start_s = clock();
    while (loop--)
    {
        result = SignMessage(privateKey, message, signature);
        if (result == false)
        {
            break;
        }
        if (loop != 0)
        {
            signature.clear();
        }
    }
    int stop_s = clock();
    double etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

    if (result == true)
    {
        wcout << endl;
        wcout << "Successfully Signing Message!" << endl
              << endl;
        StringSource(signature, true, new HexEncoder(new StringSink(hex_signature)));

        wcout << "Signature(hex): " << string_to_wstring(hex_signature) << endl;
        wcout << "Total excecution time for 10000 loop: " << etime << "ms" << endl;
        wcout << "Average execution time for 10000 loop: " << etime / 10000 << "ms" << endl;
    }
    else
    {
        wcout << "Failure Signing Message!" << endl;
    }
}

void Verify()
{
    string message, signature;

    // Public keys for verifying
    CryptoPP::ECDSA<ECP, SHA1>::PublicKey publicKey;

    wcout << endl;
    wcout << "[+] Verifying" << endl;
    message = Input_Message();
    signature = Input_Signature();

    wcout << "Input the file name of public key: ";
   

#ifdef __linux__
        __fpurge(stdin);
#elif _WIN32
        fflush(stdin);
#else
#endif
        wstring key_filename;
        getline(wcin, key_filename);

        // Load key in PKCS#9 and X.509 format
        LoadPublicKey(wstring_to_string(key_filename), publicKey);

        wcout << "Message: " << string_to_wstring(message) << endl;

        string hex_signature;

        StringSource(signature, true, new HexEncoder(new StringSink(hex_signature)));

        wcout << "Signature(hex): " << string_to_wstring(hex_signature) << endl;

        PrintPublicKey(publicKey);

        int loop = 10000;
        bool result;
        int start_s = clock();
        while (loop--)
        {
            result = VerifyMessage(publicKey, message, signature);
            if (result == false)
            {
                break;
            }
    }
    int stop_s = clock();
    double etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;

    if (result == true)
    {
        wcout << endl;
        wcout << "Successfully Verify Message!" << endl;
        wcout << "Signature(hex): " << string_to_wstring(hex_signature) << endl;
        wcout << "Total excecution time for 10000 loop: " << etime << "ms" << endl;
        wcout << "Average execution time for 10000 loop: " << etime / 10000 << "ms" << endl;
    }
    else
    {
        wcout << "Failure Verify Message!";
    }
}

void Input_PrivateKey(ECDSA<ECP, SHA1>::PrivateKey &key)
{
    do
    {
        wcout << endl;
        wcout << "[+] Input Private Key\n";
        wcout << "[1] Key from file\n";
        wcout << "[2] Random key and save to file\n";
        wcout << "Enter Option: ";
        int option;
        wcin >> option;
        if (option == 1)
        {
            wcout << "Input the file name of private key: ";
            wstring key_filename;

#ifdef __linux__
            __fpurge(stdin);
#elif _WIN32
            fflush(stdin);
#else
#endif

            getline(wcin, key_filename);

            // Load key in PKCS#9 and X.509 format
            LoadPrivateKey(wstring_to_string(key_filename), key);
            return;
        }
        else if (option == 2)
        {
            // Generate random Keys
            bool result = GeneratePrivateKey(CryptoPP::ASN1::secp160r1(), key);
            if (result == true)
            {
                wcout << "Successfully generate key!\n";
                wcout << "Input the file name to save private key: ";
                wstring key_filename;

#ifdef __linux__
                __fpurge(stdin);
#elif _WIN32
                fflush(stdin);
#else
#endif

                getline(wcin, key_filename);

                // Save key in PKCS#9 and X.509 format
                SavePrivateKey(wstring_to_string(key_filename), key);

                CryptoPP::ECDSA<ECP, SHA1>::PublicKey publicKey;
                bool result_pubKey = GeneratePublicKey(key, publicKey);
                if (result_pubKey == true)
                {
                    wcout << "Succesfully generate public key from private key\n";

                    wcout << "Input the file name to save public key: ";
                    key_filename.clear();

#ifdef __linux__
                    __fpurge(stdin);
#elif _WIN32
                    fflush(stdin);
#else
#endif

                    getline(wcin, key_filename);

                    SavePublicKey(wstring_to_string(key_filename), publicKey);
                }
                return;
            }
            else
            {
                wcout << "Failure generate key!\n";
                continue;
            }
        }
        else
        {
            wcout << "Invalid option!\n";
        }
    } while (1);
}
