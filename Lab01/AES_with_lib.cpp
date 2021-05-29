// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <ctime>
#include <iomanip>

#include <iostream>
#include "assert.h"

// library for unicode in C++
/* Vietnamese support */
/* Set _setmode()*/
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else
#endif

#include <string>
#include <locale>
#include <codecvt>
using std::cerr;
using std::endl;
using std::wcin;
using std::wcout;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;
#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include "cryptopp/hex.h"
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include "cryptopp/filters.h"
using CryptoPP::Redirector;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;

#include <cryptopp/files.h>
using CryptoPP::AuthenticatedDecryptionFilter;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::BufferedTransformation;
using CryptoPP::FileSink;
using CryptoPP::FileSource;

using CryptoPP::FileSource;
using CryptoPP::StringSource;

#include "cryptopp/AES.h"
using CryptoPP::AES;

#include "cryptopp/modes.h"
#include "cryptopp/xts.h"
#include "cryptopp/gcm.h"
#include "cryptopp/ccm.h"
using CryptoPP::CBC_CTS_Mode; //done
using CryptoPP::CBC_Mode;     // done
using CryptoPP::CCM;
using CryptoPP::CFB_Mode; //done
using CryptoPP::CTR_Mode; //done
using CryptoPP::ECB_Mode; // done
using CryptoPP::GCM;
using CryptoPP::GCM_TablesOption;
using CryptoPP::OFB_Mode; //done
using CryptoPP::XTS;

#include "cryptopp/secblock.h"
using CryptoPP::byte;
using CryptoPP::SecByteBlock;

const int TAG_SIZE = 16;

// CBC encrypt
double CBC_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
    // executation time of each Encryption operation
    int start_s = clock();
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with CBC mode
        CBC_Mode<AES>::Encryption e;
        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds default padding ( without argument specified)
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        // stream StreamTransformationFilter
        //pipepline the plaintext to the AES scheme (e) through StreamTransformationFilter and output to cipher string
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)) // StreamTransformationFilter
        );                                                                  // StringSource
        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        // cerr << e.what() << " here "<<endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CBC decrypt
double CBC_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode CBC
        CBC_Mode<AES>::Decryption d;
        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        // pipeline the cipher to AES Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)) // StreamTransformationFilter
        );

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        // cerr << e.what() <<"hehe"<< endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// EBC encrypt
double ECB_AES_Encrypt(string plain, SecByteBlock key, string &cipher)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with ECB mode
        ECB_Mode<AES>::Encryption e;

        // set key for AES encryption scheme
        e.SetKey(key, key.size());

        // The StreamTransformationFilter adds default padding ( without argument specified)
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        // stream StreamTransformationFilter
        //pipepline the plaintext to the AES scheme (e) through StreamTransformationFilter and output to cipher string
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)) // StreamTransformationFilter
        );                                                                  // StringSource
        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// EBC decrypt
double ECB_AES_Decrypt(string cipher, SecByteBlock key, string &recovered)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode ECB
        ECB_Mode<AES>::Decryption d;
        // set key for operation
        d.SetKey(key, key.size());

        // The StreamTransformationFilter removes
        //  padding as required.
        // pipeline the cipher to AES Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)) // StreamTransformationFilter
        );

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}
// CBC-CTS encrypt
double CBC_CTS_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with CBC-CTS mode
        CBC_CTS_Mode<AES>::Encryption e;

        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds default padding ( without argument specified)
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        // stream StreamTransformationFilter
        //pipepline the plaintext to the AES scheme (e) through StreamTransformationFilter and output to cipher string
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)) // StreamTransformationFilter
        );                                                                  // StringSource
        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CBC-CTS decrypt
double CBC_CTS_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode CBC-CTS
        CBC_CTS_Mode<AES>::Decryption d;
        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        // pipeline the cipher to AES Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)) // StreamTransformationFilter
        );

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CFB encrypt
double CFB_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with CFB mode
        CFB_Mode<AES>::Encryption e;

        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds default padding ( without argument specified)
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        // stream StreamTransformationFilter
        //pipepline the plaintext to the AES scheme (e) through StreamTransformationFilter and output to cipher string
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)) // StreamTransformationFilter
        );                                                                  // StringSource
        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CFB decrypt
double CFB_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode CFB
        CFB_Mode<AES>::Decryption d;
        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        // pipeline the cipher to AES Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)) // StreamTransformationFilter
        );

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CTR encrypt
double CTR_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with CTR mode
        CTR_Mode<AES>::Encryption e;

        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds default padding ( without argument specified)
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        // stream StreamTransformationFilter
        //pipepline the plaintext to the AES scheme (e) through StreamTransformationFilter and output to cipher string
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)) // StreamTransformationFilter
        );                                                                  // StringSource
        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CTR decrypt
double CTR_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode CTR
        CTR_Mode<AES>::Decryption d;
        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        // pipeline the cipher to AES Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)) // StreamTransformationFilter
        );

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// OFB encrypt
double OFB_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with OFB mode
        OFB_Mode<AES>::Encryption e;
        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds default padding ( without argument specified)
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        // stream StreamTransformationFilter
        //pipepline the plaintext to the AES scheme (e) through StreamTransformationFilter and output to cipher string
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)) // StreamTransformationFilter
        );                                                                  // StringSource
        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// OFB decrypt
double OFB_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode OFB
        OFB_Mode<AES>::Decryption d;
        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        // pipeline the cipher to AES Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)) // StreamTransformationFilter
        );

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}
// XTS encrypt
double XTS_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with XTS mode
        XTS_Mode<AES>::Encryption e;

        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds default padding ( without argument specified)
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        // stream StreamTransformationFilter
        //pipepline the plaintext to the AES scheme (e) through StreamTransformationFilter and output to cipher string
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)) // StreamTransformationFilter
        );                                                                  // StringSource
        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// XTS decrypt
double XTS_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode XTS
        XTS_Mode<AES>::Decryption d;
        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        // pipeline the cipher to AES Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)) // StreamTransformationFilter
        );

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (const CryptoPP::Exception &e)
    {
        // show any exception when catched
        cerr << e.what() << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// GCM encrypt
double GCM_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher, int iv_length, string &adata)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with GCM mode
        GCM<AES>::Encryption e;
        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv, iv_length);

        // Authentication Encryption Filter
        AuthenticatedEncryptionFilter ef(e, new StringSink(cipher), false, TAG_SIZE);

        // AuthenticatedEncryptionFilter::ChannelPut
        //  defines two channels: "" (empty) and "AAD"
        //   channel "" is encrypted and authenticated
        //   channel "AAD" is authenticated
        ef.ChannelPut("AAD", (const byte *)adata.data(), adata.size());
        ef.ChannelMessageEnd("AAD");

        // Authenticated data *must* be pushed before
        //  Confidential/Authenticated data. Otherwise
        //  we must catch the BadState exception
        ef.ChannelPut("", (const byte *)plain.data(), plain.size());
        ef.ChannelMessageEnd("");

        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (CryptoPP::BufferedTransformation::NoChannelSupport &e)
    {
        // The tag must go in to the default channel:
        //  "unknown: this object doesn't support multiple channels"
        std::wcerr << "Caught NoChannelSupport..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::AuthenticatedSymmetricCipher::BadState &e)
    {
        // Pushing PDATA before ADATA results in:
        //  "GMC/AES: Update was called before State_IVSet"
        std::wcerr << "Caught BadState..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::InvalidArgument &e)
    {
        std::wcerr << "Caught InvalidArgument..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// GCM decrypt
double GCM_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered, int iv_length, string radata, string plain)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode GCM
        GCM<AES>::Decryption d;
        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv, iv_length);

        // break the cipher text out into it's
        // components: Encrypted Data and MAC value

        string enc = cipher.substr(0, cipher.length() - TAG_SIZE);
        string mac = cipher.substr(cipher.length() - TAG_SIZE);

        // Sanity checks
        assert(cipher.size() == enc.size() + mac.size());
        assert(enc.size() == plain.size());
        assert(mac.size() == TAG_SIZE);

        // Object will not throw an exception
        //  during decryption\verification _if_
        //  verification fails.
        //AuthenticatedDecryptionFilter df( d, NULL,
        // AuthenticatedDecryptionFilter::MAC_AT_BEGIN );

        AuthenticatedDecryptionFilter df(d, NULL,
                                         AuthenticatedDecryptionFilter::MAC_AT_BEGIN |
                                             AuthenticatedDecryptionFilter::THROW_EXCEPTION,
                                         TAG_SIZE);

        // The order of the following calls are important
        df.ChannelPut("", (const byte *)mac.data(), mac.size());
        df.ChannelPut("AAD", (const byte *)radata.data(), radata.size());
        df.ChannelPut("", (const byte *)enc.data(), enc.size());

        // If the object throws, it will most likely occur
        //  during ChannelMessageEnd()
        df.ChannelMessageEnd("AAD");
        df.ChannelMessageEnd("");

        // If the object does not throw, here's the only
        //  opportunity to check the data's integrity
        bool b = false;
        b = df.GetLastResult();
        assert(b == true);

        // Remove data from channel
        size_t n = (size_t)-1;

        // Plain text recoverd from enc.data()
        df.SetRetrievalChannel("");
        n = (size_t)df.MaxRetrievable();
        recovered.resize(n);

        if (n > 0)
        {
            df.Get((byte *)recovered.data(), n);
        }

        assert(plain == recovered);

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (CryptoPP::InvalidArgument &e)
    {
        std::wcerr << "Caught InvalidArgument..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::AuthenticatedSymmetricCipher::BadState &e)
    {
        // Pushing PDATA before ADATA results in:
        //  "GMC/AES: Update was called before State_IVSet"
        std::wcerr << "Caught BadState..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::HashVerificationFilter::HashVerificationFailed &e)
    {
        std::wcerr << "Caught HashVerificationFailed..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CCM mode
double CCM_AES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher, int iv_length, string &adata)
{
    int start_s = clock();
    // executation time of each Encryption operation
    double etime = 0;
    // try catch exception during operation
    try
    {
        // encrytion AES with CCM mode
        CCM<AES, TAG_SIZE>::Encryption e;
        // set key for AES encryption scheme
        e.SetKeyWithIV(key, key.size(), iv, iv_length);
        e.SpecifyDataLengths(adata.size(), plain.size(), 0);
        // Authentication Encryption Filter
        AuthenticatedEncryptionFilter ef(e, new StringSink(cipher), false, TAG_SIZE);

        // AuthenticatedEncryptionFilter::ChannelPut
        //  defines two channels: "" (empty) and "AAD"
        //   channel "" is encrypted and authenticated
        //   channel "AAD" is authenticated
        ef.ChannelPut("AAD", (const byte *)adata.data(), adata.size());
        ef.ChannelMessageEnd("AAD");

        // Authenticated data *must* be pushed before
        //  Confidential/Authenticated data. Otherwise
        //  we must catch the BadState exception
        ef.ChannelPut("", (const byte *)plain.data(), plain.size());
        ef.ChannelMessageEnd("");

        // time done for encryption operation
        int stop_s = clock();
        // compute the operating execution from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }
    catch (CryptoPP::BufferedTransformation::NoChannelSupport &e)
    {
        // The tag must go in to the default channel:
        //  "unknown: this object doesn't support multiple channels"
        std::wcerr << "Caught NoChannelSupport..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::AuthenticatedSymmetricCipher::BadState &e)
    {
        // Pushing PDATA before ADATA results in:
        //  "GMC/AES: Update was called before State_IVSet"
        std::wcerr << "Caught BadState..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::InvalidArgument &e)
    {
        std::wcerr << "Caught InvalidArgument..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// CCM decrypt
double CCM_AES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered, int iv_length, string radata, string plain)
{
    int start_s = clock();
    // execution time of AES decryption operation
    double etime = 0;

    // catch any exception during operation
    try
    {
        // initiate AES decryption with mode CCM
        CCM<AES>::Decryption d;

        // set key for operation
        d.SetKeyWithIV(key, key.size(), iv, iv_length);

        // break the cipher text out into it's
        // components: Encrypted Data and MAC value

        string enc = cipher.substr(0, cipher.length() - TAG_SIZE);
        string mac = cipher.substr(cipher.length() - TAG_SIZE);
        d.SpecifyDataLengths(radata.size(), enc.size(), 0);

        // Sanity checks
        assert(cipher.size() == enc.size() + mac.size());
        assert(enc.size() == plain.size());
        assert(mac.size() == TAG_SIZE);

        AuthenticatedDecryptionFilter df(d, NULL,
                                         AuthenticatedDecryptionFilter::MAC_AT_BEGIN |
                                             AuthenticatedDecryptionFilter::THROW_EXCEPTION,
                                         TAG_SIZE);

        // The order of the following calls are important
        df.ChannelPut("", (const byte *)mac.data(), mac.size());
        df.ChannelPut("AAD", (const byte *)radata.data(), radata.size());
        df.ChannelPut("", (const byte *)enc.data(), enc.size());

        // If the object throws, it will most likely occur
        //  during ChannelMessageEnd()
        df.ChannelMessageEnd("AAD");
        df.ChannelMessageEnd("");

        // If the object does not throw, here's the only
        //  opportunity to check the data's integrity
        bool b = false;
        b = df.GetLastResult();
        assert(b == true);

        // Remove data from channel
        size_t n = (size_t)-1;

        // Plain text recoverd from enc.data()
        df.SetRetrievalChannel("");
        n = (size_t)df.MaxRetrievable();
        recovered.resize(n);

        if (n > 0)
        {
            df.Get((byte *)recovered.data(), n);
        }

        assert(plain == recovered);

        // time done for decryption operation																 // StringSource
        int stop_s = clock();
        // compute time for operating execution time from the start time to end time
        etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    }

    catch (CryptoPP::InvalidArgument &e)
    {
        std::wcerr << "Caught InvalidArgument..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::AuthenticatedSymmetricCipher::BadState &e)
    {
        // Pushing PDATA before ADATA results in:
        //  "GMC/AES: Update was called before State_IVSet"
        std::wcerr << "Caught BadState..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }
    catch (CryptoPP::HashVerificationFilter::HashVerificationFailed &e)
    {
        std::wcerr << "Caught HashVerificationFailed..." << endl;
        std::wcerr << e.what() << endl;
        std::wcerr << endl;
        exit(1);
    }

    // return execution time
    return etime;
}

// show the result out screen (console)
void show_result(SecByteBlock key, byte *iv, int iv_length, string ciphertext, string recovered, double total_time_encrypt, double total_time_decrypt, string mode)
{
    string encoded;
    // clear encoded
    encoded.clear();
    // convert key to hex format and save to encoded string

    StringSource(key, key.size(), true,
                 new HexEncoder(
                     new StringSink(encoded)) // HexEncoder
    );
    // StringSource
    // show key in hex format
    wcout << "Key: " << encoded.c_str() << endl;

    if (mode != "ECB")
    {
        // convert iv to hex format and save to encoded string
        encoded.clear();
        StringSource(iv, iv_length, true,
                     new HexEncoder(
                         new StringSink(encoded)) // HexEncoder
        );
        // show iv in hex format
        // StringSource
        wcout << "iv:  " << encoded.c_str() << endl;
    }

    // clear encoded
    encoded.clear();
    // convert ciphertext to hex format and save to encoded string
    StringSource(ciphertext, true,
                 new HexEncoder(
                     new StringSink(encoded)) // HexEncoder
    );                                        // StringSource
    // show cipher text in hex format
    wcout << "Cipher text: " << encoded.c_str() << endl;
    double ex_time_encrypt = total_time_encrypt / 10000; // Average execution time of 10.000 encryption running

    // compute the average time of each decryption
    double ex_time_decrypt = total_time_decrypt / 10000; // Average execution time of 10.000 decryption running
    // compute the average time of each encryption

    // show result to console screen
    wcout << "Total execution time for 10.000 rounds: \t"
          << "encrypt: " << total_time_encrypt << "ms\t decrypt: " << total_time_decrypt << "ms" << endl;
    // setw(41) to format output
    wcout << std::setw(41) << std::left << "Execution time: \t"
          << "encrypt: " << ex_time_encrypt << "ms\tdecrypt: " << ex_time_decrypt << "ms" << endl;

    // show decode message
    // show decode message and convert to utf16
    std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(recovered);
    wcout << "Recoverd text: " << str << endl;
}

double Estimation_En_De_cypt_Operation(string &plain, byte *iv, SecByteBlock key, string &cipher, int mode, bool is_decryption, int loop, string &adata, int iv_length)
{
    double total_time = 0;

    string pdata = plain;
    while (loop--)
    {

        // Compute total time for encryption
        switch (mode)
        {
        case 1:
            // ECB mode
            if (!is_decryption)
            {
                total_time += ECB_AES_Encrypt(plain, key, cipher);
            }
            else
            {
                total_time += ECB_AES_Decrypt(cipher, key, plain);
            }
            break;
        case 2:
            // CBC mode
            if (!is_decryption)
            {
                total_time += CBC_AES_Encrypt(plain, iv, key, cipher);
            }
            else
            {
                total_time += CBC_AES_Decrypt(cipher, iv, key, plain);
            }
            break;
        case 3:
            // CBC CTS mode
            if (!is_decryption)
            {
                total_time += CBC_CTS_AES_Encrypt(plain, iv, key, cipher);
            }
            else
            {
                total_time += CBC_CTS_AES_Decrypt(cipher, iv, key, plain);
            }
            break;
        case 4:
            // CFB mode
            if (!is_decryption)
            {
                total_time += CFB_AES_Encrypt(plain, iv, key, cipher);
            }
            else
            {

                total_time += CFB_AES_Decrypt(cipher, iv, key, plain);
            }
            break;
        case 5:
            // CTR mode
            if (!is_decryption)
            {

                total_time += CTR_AES_Encrypt(plain, iv, key, cipher);
            }
            else
            {
                total_time += CTR_AES_Decrypt(cipher, iv, key, plain);
            }
            break;
        case 6:
            // OFB mode
            if (!is_decryption)
            {

                total_time += OFB_AES_Encrypt(plain, iv, key, cipher);
            }
            else
            {
                total_time += OFB_AES_Decrypt(cipher, iv, key, plain);
            }
            break;
        case 7:
            //XTS mode
            if (!is_decryption)
            {
                total_time += XTS_AES_Encrypt(plain, iv, key, cipher);
            }
            else
            {
                total_time += XTS_AES_Decrypt(cipher, iv, key, plain);
            }
            break;
        case 8:
            //GCM mode authentication
            if (!is_decryption)
            {
                total_time += GCM_AES_Encrypt(plain, iv, key, cipher, iv_length, adata);
            }
            else
            {
                total_time += GCM_AES_Decrypt(cipher, iv, key, plain, iv_length, adata, pdata);
            }
            break;
        case 9:
            //CCM mode authentication
            if (!is_decryption)
            {
                total_time += CCM_AES_Encrypt(plain, iv, key, cipher, iv_length, adata);
            }
            else
            {
                total_time += CCM_AES_Decrypt(cipher, iv, key, plain, iv_length, adata, pdata);
            }
            break;

        default:
            break;
        }

        // save the ciphertext to show for the last loop
        if (loop == 0)
        {
            break;
        }
        if (!is_decryption)
        {
            cipher.clear();
        }
        else
        {
            plain.clear();
        }
    }
    return total_time;
}
SecByteBlock input_key_from_keyboard(int key_length)
{
    std::wstring key_input;
    string input = "";
    do
    {
        wcout << "Input key: ";
        fflush(stdin);
        std::getline(wcin, key_input);
        input = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(key_input);

        if (input.length() != key_length)
        {
            wcout << "Wrong key length input. Key length must be 16 bytes!\n";
        }
        else
        {
            break;
        }
    } while (1);
    SecByteBlock key(key_length);
    for (int i = 0; i < key_length; i++)
    {
        key[i] = (unsigned int)input[i];
    }
    return key;
}
int key_length_selection(int mode)
{
    int key_length_bytes;
    int key1 = 16, key2 = 24, key3 = 32;
    do
    {
        wcout << "Input key length:" << endl;
        if (mode != 7)
        {
            wcout << "16 bytes - 128 bits key\n";
            wcout << "24 bytes - 192 bits key\n";
            wcout << "32 bytes - 256 bits key\n";
        }
        else
        {
            wcout << "32 bytes - 256 bits key\n";
            wcout << "48 bytes - 348 bits key\n";
            wcout << "64 bytes - 512 bits key\n";
            key1 = 32;
            key2 = 48;
            key3 = 64;
        }
        wcout << "Enter key length: ";
        wcin >> key_length_bytes;
        if (key_length_bytes != key1 && key_length_bytes != key2 && key_length_bytes != key3)
        {
            wcout << "Wrong key length input!" << endl;
        }
        else
        {
            break;
        }
    } while (1);
    return key_length_bytes;
}
SecByteBlock key_selection(int mode)
{
    int key_length = key_length_selection(mode);

    SecByteBlock key(key_length);

    int option_input_key = 0;
    do
    {
        wcout << endl;
        wcout << "[+] Key selection:\n";
        wcout << "1 - input key from keyboard\n";
        wcout << "2 - input key from file\n";
        wcout << "3 - generate a ramdom key\n";
        wcout << "Enter option: ";
        wcin >> option_input_key;
        if (option_input_key >= 1 && option_input_key <= 3)
        {
            break;
        }
        else
        {
            wcout << "Wrong input.\n";
        }
    } while (1);

    switch (option_input_key)
    {
    case 1:
    {
        key = input_key_from_keyboard(key_length);
        break;
    }
    case 2:
    {
        // reading key from file
        try
        {
            FileSource fs("AES_key.key", false);
            // create space for key
            CryptoPP::ArraySink copykey(key, key.size());
            //copy data from AES_key.key to key
            fs.Detach(new Redirector(copykey));
            fs.Pump(key_length);
        }
        catch (CryptoPP::Exception e)
        {
            string error = e.GetWhat();
            std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(error);
            wcout << str << endl;
            exit(1);
        }
        break;
    }
    case 3:
    {
        AutoSeededRandomPool prng;
        prng.GenerateBlock(key, key_length);
        break;
    }
    }
    if (option_input_key != 2)
    {
        StringSource ss(key, key.size(), true, new FileSink("AES_key.key"));
        wcout << "Key has been save to AES_key.key" << endl;
    }
    return key;
}
byte *input_iv_from_keyboard(int iv_length)
{
    std::wstring iv_input;
    string input = "";
    do
    {
        wcout << "Input key: ";
        fflush(stdin);
        std::getline(wcin, iv_input);
        input = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(iv_input);
        if (input.length() != iv_length)
        {
            wcout << "Wrong iv length input. iv length must be " << iv_length << " bytes!\n";
        }
        else
        {
            break;
        }
    } while (1);
    byte *iv = new byte[iv_length];
    for (int i = 0; i < iv_length; i++)
    {
        iv[i] = (unsigned int)input[i];
    }
    return iv;
}
long selection_iv_length_authentication_mode(int min, long long max)
{
    do
    {

        wcout << "\n[+] IV selection for authentication mode:\n";
        wcout << "Enter a iv length in range (" << min << "-" << max << "): ";
        long length = 0;
        wcin >> length;
        if (length <= min && length > max)
        {
            wcout << "Wrong input iv length!\n";
        }
        else
        {
            return length;
        }
    } while (1);
}
byte *iv_selection(int mode, unsigned int &iv_length)
{
    byte *iv;
    int option_input_iv = 0;
    iv_length = 16;
    if (mode == 8)
    {
        iv_length = selection_iv_length_authentication_mode(1, 4294967295);
    }
    if (mode == 9)
    {
        iv_length = selection_iv_length_authentication_mode(7, 13);
    }
    do
    {
        wcout << endl;
        wcout << "[+] IV selection:\n";
        wcout << "1 - input iv from keyboard\n";
        wcout << "2 - input iv from file\n";
        wcout << "3 - generate a ramdom iv\n";
        wcout << "Enter option: ";
        wcin >> option_input_iv;
        if (option_input_iv >= 1 && option_input_iv <= 3)
        {
            break;
        }
        else
        {
            wcout << "Wrong input.\n";
        }
    } while (1);

    switch (option_input_iv)
    {
    case 1:
    {
        iv = input_iv_from_keyboard(iv_length);
        break;
    }
    case 2:
    {
        // reading key from file
        try
        {
            iv = new byte[iv_length];
            FileSource fs("AES_iv.iv", false);
            // create space for key
            CryptoPP::ArraySink copykey(iv, iv_length);
            //copy data from AES_key.key to key
            fs.Detach(new Redirector(copykey));
            fs.Pump(iv_length);
        }
        catch (CryptoPP::Exception e)
        {
            string error = e.GetWhat();
            std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(error);
            wcout << str << endl;
            exit(1);
        }
        break;
    }
    case 3:
    {
        iv = new byte[iv_length];
        AutoSeededRandomPool prng;
        prng.GenerateBlock(iv, iv_length);
        break;
    }
    }
    if (option_input_iv != 2)
    {
        StringSource ss(iv, iv_length, true, new FileSink("AES_iv.iv"));
        wcout << "iv has been saved to AES_iv.iv" << endl;
    }
    return iv;
}
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

    // set default plaintext
    std::wstring wplaintext = L"Welcome to the AES encryption and decryption!";
    wcout << "\n[+] Enter plaintext: ";
    std::getline(wcin, wplaintext);

    // random byte
    AutoSeededRandomPool prng;
    // key initiattion
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);

    byte *iv;

    int mode_option = 0;

    // Select operation mode
    do
    {
        wcout << endl;
        wcout << "[+] Select operation mode: \n";
        wcout << "1 - EBC mode\n";
        wcout << "2 - CBC mode\n";
        wcout << "3 - CBC CTS mode\n";
        wcout << "4 - CFB mode\n";
        wcout << "5 - CTR mode\n";
        wcout << "6 - OFB mode\n";
        wcout << "7 - XTS mode\n";
        wcout << "8 - GCM mode\n";
        wcout << "9 - CCM mode\n";
        wcout << "Enter selection (1-9): ";

        wcin >> mode_option;
        if (mode_option < 1 || mode_option > 9)
        {
            wcout << "Input wrong options!\n";
        }
        else
        {
            break;
        }
    } while (1);

    key = key_selection(mode_option);

    unsigned int iv_length = 16;
    // not set iv for ECB mode
    if (mode_option != 1)
    {
        iv = iv_selection(mode_option, iv_length);
    }
    else
    {
        iv = NULL;
    }

    std::wstring w_adata = L"";
    string adata = "";
    const int TAG_SIZE = 16;
    // input authentication data for authentication mode
    if (mode_option == 8 || mode_option == 9)
    {

        wcout << "\n[+] Enter authentication data: ";
        fflush(stdin);
        std::getline(wcin, w_adata);

        // convert wstring(utf8) to string
        adata = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(w_adata);
    }

    // convert input in utf16 to string
    string plaintext = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wplaintext);

    // initiate ciphertext, encoded for key in hex format, recoverd is decryption message in hex format

    string ciphertext, recovered;

    // initiate for time variable
    // Total time for 10.000 encryption running
    double total_time_encrypt = 0;

    // Total time for 10.000 decryption running
    double total_time_decrypt = 0;
    // initiate start time

    // loop for 10.000 operation
    int loop = 10000;
    total_time_encrypt = Estimation_En_De_cypt_Operation(plaintext, iv, key, ciphertext, mode_option, 0, loop, adata, iv_length);

    total_time_decrypt = Estimation_En_De_cypt_Operation(recovered, iv, key, ciphertext, mode_option, 1, loop, adata, iv_length);

    string mode_str[] = {"ECB", "CBC", "CBC CTS", "CFB", "CTR", "OFB", "XTS", "GCM", "CCM"};
    wcout << endl;
    wcout << "[+] Estimation result" << endl;
    show_result(key, iv, iv_length, ciphertext, recovered, total_time_encrypt, total_time_decrypt, mode_str[mode_option - 1]);
    return 0;
}
