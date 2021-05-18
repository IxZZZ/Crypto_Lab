// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <ctime>
#include <iomanip>

#include <iostream>
// library for unicode in C++
#include <fcntl.h> //_O_WTEXT
#include <io.h>	   //_setmode()
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
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/des.h"
using CryptoPP::DES;

#include "cryptopp/modes.h"
using CryptoPP::CBC_CTS_Mode; //done
using CryptoPP::CBC_Mode;	  // done
using CryptoPP::CFB_Mode;	  //done
using CryptoPP::CTR_Mode;	  //done
using CryptoPP::ECB_Mode;	  // done
using CryptoPP::OFB_Mode;	  //done

#include "cryptopp/secblock.h"
using CryptoPP::byte;
using CryptoPP::SecByteBlock;

// CBC encrypt
double CBC_DES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
	// executation time of each Encryption operation
	int start_s = clock();
	double etime = 0;
	// try catch exception during operation
	try
	{
		// encrytion DES with CBC mode
		CBC_Mode<DES>::Encryption e;
		// set key for DES encryption scheme
		e.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter adds default padding ( without argument specified)
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		// stream StreamTransformationFilter
		//pipepline the plaintext to the DES scheme (e) through StreamTransformationFilter and output to cipher string
		StringSource(plain, true,
					 new StreamTransformationFilter(e,
													new StringSink(cipher)) // StreamTransformationFilter
		);																	// StringSource
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
double CBC_DES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
	int start_s = clock();
	// execution time of DES decryption operation
	double etime = 0;

	// catch any exception during operation
	try
	{
		// initiate DES decryption with mode CBC
		CBC_Mode<DES>::Decryption d;
		// set key for operation
		d.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		// pipeline the cipher to Des Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
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
double ECB_DES_Encrypt(string plain, SecByteBlock key, string &cipher)
{
	int start_s = clock();
	// executation time of each Encryption operation
	double etime = 0;
	// try catch exception during operation
	try
	{
		// encrytion DES with ECB mode
		ECB_Mode<DES>::Encryption e;

		// set key for DES encryption scheme
		e.SetKey(key, key.size());

		// The StreamTransformationFilter adds default padding ( without argument specified)
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		// stream StreamTransformationFilter
		//pipepline the plaintext to the DES scheme (e) through StreamTransformationFilter and output to cipher string
		StringSource(plain, true,
					 new StreamTransformationFilter(e,
													new StringSink(cipher)) // StreamTransformationFilter
		);																	// StringSource
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
double ECB_DES_Decrypt(string cipher, SecByteBlock key, string &recovered)
{
	int start_s = clock();
	// execution time of DES decryption operation
	double etime = 0;

	// catch any exception during operation
	try
	{
		// initiate DES decryption with mode ECB
		ECB_Mode<DES>::Decryption d;
		// set key for operation
		d.SetKey(key, key.size());

		// The StreamTransformationFilter removes
		//  padding as required.
		// pipeline the cipher to Des Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
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
double CBC_CTS_DES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
	int start_s = clock();
	// executation time of each Encryption operation
	double etime = 0;
	// try catch exception during operation
	try
	{
		// encrytion DES with CBC-CTS mode
		CBC_CTS_Mode<DES>::Encryption e;

		// set key for DES encryption scheme
		e.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter adds default padding ( without argument specified)
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		// stream StreamTransformationFilter
		//pipepline the plaintext to the DES scheme (e) through StreamTransformationFilter and output to cipher string
		StringSource(plain, true,
					 new StreamTransformationFilter(e,
													new StringSink(cipher)) // StreamTransformationFilter
		);																	// StringSource
		// time done for encryption operation
		int stop_s = clock();
		// compute the operating execution from the start time to end time
		etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
	}
	catch (const CryptoPP::Exception &e)
	{
		// show any exception when catched
		// cerr << e.what() << endl;
		exit(1);
	}

	// return execution time
	return etime;
}

// CBC-CTS decrypt
double CBC_CTS_DES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
	int start_s = clock();
	// execution time of DES decryption operation
	double etime = 0;

	// catch any exception during operation
	try
	{
		// initiate DES decryption with mode CBC-CTS
		CBC_CTS_Mode<DES>::Decryption d;
		// set key for operation
		d.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		// pipeline the cipher to Des Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
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
double CFB_DES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
	int start_s = clock();
	// executation time of each Encryption operation
	double etime = 0;
	// try catch exception during operation
	try
	{
		// encrytion DES with CFB mode
		CFB_Mode<DES>::Encryption e;

		// set key for DES encryption scheme
		e.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter adds default padding ( without argument specified)
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		// stream StreamTransformationFilter
		//pipepline the plaintext to the DES scheme (e) through StreamTransformationFilter and output to cipher string
		StringSource(plain, true,
					 new StreamTransformationFilter(e,
													new StringSink(cipher)) // StreamTransformationFilter
		);																	// StringSource
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
double CFB_DES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
	int start_s = clock();
	// execution time of DES decryption operation
	double etime = 0;

	// catch any exception during operation
	try
	{
		// initiate DES decryption with mode CFB
		CFB_Mode<DES>::Decryption d;
		// set key for operation
		d.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		// pipeline the cipher to Des Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
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
double CTR_DES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
	int start_s = clock();
	// executation time of each Encryption operation
	double etime = 0;
	// try catch exception during operation
	try
	{
		// encrytion DES with CTR mode
		CTR_Mode<DES>::Encryption e;

		// set key for DES encryption scheme
		e.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter adds default padding ( without argument specified)
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		// stream StreamTransformationFilter
		//pipepline the plaintext to the DES scheme (e) through StreamTransformationFilter and output to cipher string
		StringSource(plain, true,
					 new StreamTransformationFilter(e,
													new StringSink(cipher)) // StreamTransformationFilter
		);																	// StringSource
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
double CTR_DES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
	int start_s = clock();
	// execution time of DES decryption operation
	double etime = 0;

	// catch any exception during operation
	try
	{
		// initiate DES decryption with mode CTR
		CTR_Mode<DES>::Decryption d;
		// set key for operation
		d.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		// pipeline the cipher to Des Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
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
double OFB_DES_Encrypt(string plain, byte *iv, SecByteBlock key, string &cipher)
{
	int start_s = clock();
	// executation time of each Encryption operation
	double etime = 0;
	// try catch exception during operation
	try
	{
		// encrytion DES with OFB mode
		OFB_Mode<DES>::Encryption e;
		// set key for DES encryption scheme
		e.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter adds default padding ( without argument specified)
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		// stream StreamTransformationFilter
		//pipepline the plaintext to the DES scheme (e) through StreamTransformationFilter and output to cipher string
		StringSource(plain, true,
					 new StreamTransformationFilter(e,
													new StringSink(cipher)) // StreamTransformationFilter
		);																	// StringSource
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
double OFB_DES_Decrypt(string cipher, byte *iv, SecByteBlock key, string &recovered)
{
	int start_s = clock();
	// execution time of DES decryption operation
	double etime = 0;

	// catch any exception during operation
	try
	{
		// initiate DES decryption with mode OFB
		OFB_Mode<DES>::Decryption d;
		// set key for operation
		d.SetKeyWithIV(key, key.size(), iv);

		// The StreamTransformationFilter removes
		//  padding as required.
		// pipeline the cipher to Des Decryption scheme (d) through StreamTransformationFilter and output to recoverd string
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
		// show iv in hex format									  // StringSource
		wcout << "iv: " << encoded.c_str() << endl;
	}

	// clear encoded
	encoded.clear();
	// convert ciphertext to hex format and save to encoded string
	StringSource(ciphertext, true,
				 new HexEncoder(
					 new StringSink(encoded)) // HexEncoder
	);										  // StringSource
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
	std::wstring str = std::wstring_convert<std::codecvt_utf16<wchar_t>>().from_bytes(recovered);
	wcout << "Recoverd text: " << str << endl;
}
int main(int argc, char *argv[])
{

	_setmode(_fileno(stdout), _O_WTEXT); //needed for output unicode
	_setmode(_fileno(stdin), _O_WTEXT);	 //needed for input unicode

	// set default plaintext
	std::wstring wplaintext = L"Welcome to the AES encryption and decryption!";
	wcout << "Enter plaintext: ";
	std::getline(wcin, wplaintext);

	// convert input in utf16 to string
	string plaintext = std::wstring_convert<std::codecvt_utf16<wchar_t>>().to_bytes(wplaintext);

	// initiate ciphertext, encoded for key in hex format, recoverd is decryption message in hex format
	string ciphertext_ECB_mode, recovered_ECB_mode, ciphertext_CBC_mode, recovered_CBC_mode,
		ciphertext_CFB_mode, recovered_CFB_mode, ciphertext_CBC_CTS_mode, recovered_CBC_CTS_mode,
		ciphertext_CTR_mode, recovered_CTR_mode, ciphertext_OFB_mode, recovered_OFB_mode;

	// initiate for time variable
	// Total time for 10.000 encryption running
	double total_time_encrypt_ECB_mode = 0, total_time_encrypt_CBC_mode = 0, total_time_encrypt_CFB_mode = 0, total_time_encrypt_CBC_CTS_mode = 0,
		   total_time_encrypt_CTR_mode = 0, total_time_encrypt_OFB_mode = 0,

		   // Total time for 10.000 decryption running
		total_time_decrypt_ECB_mode = 0, total_time_decrypt_CBC_mode = 0, total_time_decrypt_CFB_mode = 0, total_time_decrypt_CBC_CTS_mode = 0,
		   total_time_decrypt_CTR_mode = 0, total_time_decrypt_OFB_mode = 0;
	// initiate start time

	// loop for 10.000 operation
	int loop = 10000;
	AutoSeededRandomPool prng;
	SecByteBlock key(DES::DEFAULT_KEYLENGTH);
	byte iv[DES::BLOCKSIZE];

	while (loop--)
	{
		// set start time for encrypting operation

		// generate key with default key size, the different key for each loop
		prng.GenerateBlock(key, key.size());

		// initital vector
		// generate initial vector for CBC mode
		prng.GenerateBlock(iv, sizeof(iv));

		// Compute total time for encryption
		// CBC mode
		total_time_encrypt_CBC_mode += CBC_DES_Encrypt(plaintext, iv, key, ciphertext_CBC_mode);

		//ECB mode
		total_time_encrypt_ECB_mode += ECB_DES_Encrypt(plaintext, key, ciphertext_ECB_mode);

		// CBC-CTS mode
		total_time_encrypt_CBC_CTS_mode += CBC_CTS_DES_Encrypt(plaintext, iv, key, ciphertext_CBC_CTS_mode);

		// CFB mode
		total_time_encrypt_CFB_mode += CFB_DES_Encrypt(plaintext, iv, key, ciphertext_CFB_mode);

		// CTR mode
		total_time_encrypt_CTR_mode += CTR_DES_Encrypt(plaintext, iv, key, ciphertext_CTR_mode);

		// OFB mode
		total_time_encrypt_OFB_mode += OFB_DES_Encrypt(plaintext, iv, key, ciphertext_OFB_mode);

		// clear the decode message before running decryption
		recovered_ECB_mode.clear();
		recovered_CBC_mode.clear();
		recovered_CFB_mode.clear();
		recovered_CBC_CTS_mode.clear();
		recovered_CTR_mode.clear();
		recovered_OFB_mode.clear();

		// compute the total time Descryption
		// CBC mode
		total_time_decrypt_CBC_mode += CBC_DES_Decrypt(ciphertext_CBC_mode, iv, key, recovered_CBC_mode);

		// CFB mode
		total_time_decrypt_CFB_mode += CFB_DES_Decrypt(ciphertext_CFB_mode, iv, key, recovered_CFB_mode);

		// CBC-CTS mode
		total_time_decrypt_CBC_CTS_mode += CBC_CTS_DES_Decrypt(ciphertext_CBC_CTS_mode, iv, key, recovered_CBC_CTS_mode);

		// ECB mode
		total_time_decrypt_ECB_mode += ECB_DES_Decrypt(ciphertext_ECB_mode, key, recovered_ECB_mode);

		// CTR mode
		total_time_decrypt_CTR_mode += CTR_DES_Decrypt(ciphertext_CTR_mode, iv, key, recovered_CTR_mode);

		// OFB mode
		total_time_decrypt_OFB_mode += OFB_DES_Decrypt(ciphertext_OFB_mode, iv, key, recovered_OFB_mode);
		// save the ciphertext to show for the last loop
		if (loop == 0)
		{
			break;
		}
		ciphertext_ECB_mode.clear();
		ciphertext_CBC_mode.clear();
		ciphertext_CFB_mode.clear();
		ciphertext_CBC_CTS_mode.clear();
		ciphertext_CTR_mode.clear();
		ciphertext_OFB_mode.clear();
	}

	// plain text
	wcout << "Plaintext: " << wplaintext << endl
		  << endl;

	wcout << "---------- CBC Mode ----------" << endl;
	show_result(key, iv, sizeof(iv), ciphertext_CBC_mode, recovered_CBC_mode, total_time_encrypt_CBC_mode, total_time_decrypt_CBC_mode, "CBC");
	wcout << endl
		  << endl;

	wcout << "---------- EBC Mode ----------" << endl;
	show_result(key, iv, sizeof(iv), ciphertext_ECB_mode, recovered_ECB_mode, total_time_encrypt_ECB_mode, total_time_decrypt_ECB_mode, "ECB");
	wcout << endl
		  << endl;

	wcout << "---------- CBC-CTS Mode ----------" << endl;
	show_result(key, iv, sizeof(iv), ciphertext_CBC_CTS_mode, recovered_CBC_CTS_mode, total_time_encrypt_CBC_CTS_mode, total_time_decrypt_CBC_CTS_mode, "CBC_CTS");
	wcout << endl
		  << endl;

	wcout << "---------- CFB Mode ----------" << endl;
	show_result(key, iv, sizeof(iv), ciphertext_CFB_mode, recovered_CFB_mode, total_time_encrypt_CFB_mode, total_time_decrypt_CFB_mode, "CFB");
	wcout << endl
		  << endl;

	wcout << "---------- CTR Mode ----------" << endl;
	show_result(key, iv, sizeof(iv), ciphertext_CTR_mode, recovered_CTR_mode, total_time_encrypt_CTR_mode, total_time_decrypt_CTR_mode, "CTR");
	wcout << endl
		  << endl;

	wcout << "---------- OFB Mode ----------" << endl;
	show_result(key, iv, sizeof(iv), ciphertext_OFB_mode, recovered_OFB_mode, total_time_encrypt_OFB_mode, total_time_decrypt_OFB_mode, "OFB");
	wcout << endl
		  << endl;
	return 0;
}
