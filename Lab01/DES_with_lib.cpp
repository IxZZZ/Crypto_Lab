// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <ctime>
#include <iomanip>

#include <iostream>

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
using CryptoPP::BufferedTransformation;
using CryptoPP::FileSink;
using CryptoPP::FileSource;

using CryptoPP::FileSource;
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
		cerr << e.what() << endl;
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
		cerr << e.what() << endl;
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
		cerr << e.what() << endl;
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
	std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(recovered);
	wcout << "Recoverd text: " << str << endl;
}

double Estimation_En_De_cypt_Operation(string &plain, byte *iv, SecByteBlock key, string &cipher, int mode, bool is_decryption, int loop)
{
	double total_time = 0;
	while (loop--)
	{

		// Compute total time for encryption
		switch (mode)
		{
		case 1:
			// ECB mode
			if (!is_decryption)
			{
				total_time += ECB_DES_Encrypt(plain, key, cipher);
			}
			else
			{
				total_time += ECB_DES_Decrypt(cipher, key, plain);
			}
			break;
		case 2:
			// CBC mode
			if (!is_decryption)
			{
				total_time += CBC_DES_Encrypt(plain, iv, key, cipher);
			}
			else
			{
				total_time += CBC_DES_Decrypt(cipher, iv, key, plain);
			}
			break;
		case 3:
			// CBC CTS mode
			if (!is_decryption)
			{
				total_time += CBC_CTS_DES_Encrypt(plain, iv, key, cipher);
			}
			else
			{
				total_time += CBC_CTS_DES_Decrypt(cipher, iv, key, plain);
			}
			break;
		case 4:
			// CFB mode
			if (!is_decryption)
			{
				total_time += CFB_DES_Encrypt(plain, iv, key, cipher);
			}
			else
			{

				total_time += CFB_DES_Decrypt(cipher, iv, key, plain);
			}
			break;
		case 5:
			// CTR mode
			if (!is_decryption)
			{

				total_time += CTR_DES_Encrypt(plain, iv, key, cipher);
			}
			else
			{
				total_time += CTR_DES_Decrypt(cipher, iv, key, plain);
			}
			break;
		case 6:
			// OFB mode
			if (!is_decryption)
			{

				total_time += OFB_DES_Encrypt(plain, iv, key, cipher);
			}
			else
			{
				total_time += OFB_DES_Decrypt(cipher, iv, key, plain);
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
SecByteBlock input_key_from_keyboard()
{
	std::wstring key_input;
	string input = "";
	do
	{
		wcout << "Input key: ";
		// flush all buffet before getline
		fflush(stdin);
		std::getline(wcin, key_input);

		// convert wstring (utf8) to string (asciij)
		input = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(key_input);

		if (input.length() != 8)
		{
			// repeat input until get correct key
			wcout << "Wrong key length input. Key length must be 8 bytes!\n";
		}
		else
		{
			break;
		}

	} while (1);

	SecByteBlock key(DES::DEFAULT_KEYLENGTH);
	// convert ASCII to byte and store in key
	for (int i = 0; i < DES::DEFAULT_KEYLENGTH; i++)
	{
		key[i] = (unsigned int)input[i];
	}

	return key;
}

// input bytes key
SecByteBlock key_selection()
{

	SecByteBlock key(DES::DEFAULT_KEYLENGTH);

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
			// repeat until get correct input option
			wcout << "Wrong input.\n";
		}
	} while (1);

	switch (option_input_key)
	{
	case 1:
	{
		key = input_key_from_keyboard();
		break;
	}
	case 2:
	{
		// reading key from file
		try
		{
			FileSource fs("DES_key.key", false);
			// create space for key
			CryptoPP::ArraySink copykey(key, key.size());
			//copy data from DES_key.key to key
			fs.Detach(new Redirector(copykey));
			fs.Pump(DES::DEFAULT_KEYLENGTH);
		}
		catch (CryptoPP::Exception e)
		{
			string error = e.GetWhat();
			// print out exception when not found key file
			std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(error);
			wcout << str << endl;
			exit(0);
		}
		break;
	}
	case 3:
	{
		AutoSeededRandomPool prng;
		// generate a random bytes key
		prng.GenerateBlock(key, DES::DEFAULT_KEYLENGTH);
		break;
	}
	}
	if (option_input_key != 2)
	{
		// save the key to file
		StringSource ss(key, key.size(), true, new FileSink("DES_key.key"));
		wcout << "Key has been save to DES_key.key" << endl;
	}
	return key;
}

// enter iv from key board
byte *input_iv_from_keyboard()
{
	std::wstring iv_input;
	string input = "";
	do
	{
		wcout << "Input iv: ";
		// flush all buffer before getline
		fflush(stdin);
		std::getline(wcin, iv_input);
		// convert wstring(utf8) to string (ascii)
		input = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(iv_input);

		if (input.length() != DES::BLOCKSIZE)
		{
			wcout << "Wrong iv length input. iv length must be 8 bytes!\n";
		}
		else
		{
			break;
		}
	} while (1);
	byte *iv = new byte[DES::BLOCKSIZE];

	// convert ascii input to byte then store in iv
	for (int i = 0; i < DES::BLOCKSIZE; i++)
	{
		iv[i] = (unsigned int)input[i];
	}
	return iv;
}

// iv selection
byte *iv_selection()
{
	byte *iv;
	int option_input_iv = 0;
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
			// repeat input until get correct option
			wcout << "Wrong input.\n";
		}
	} while (1);

	switch (option_input_iv)
	{
	case 1:
	{
		iv = input_iv_from_keyboard();
		break;
	}
	case 2:
	{
		// reading key from file
		try
		{
			iv = new byte[DES::BLOCKSIZE];
			FileSource fs("DES_iv.iv", false);
			// create space for key
			CryptoPP::ArraySink copykey(iv, DES::BLOCKSIZE);
			//copy data from DES_key.key to key
			fs.Detach(new Redirector(copykey));
			fs.Pump(DES::DEFAULT_KEYLENGTH);
		}
		catch (CryptoPP::Exception e)
		{
			string error = e.GetWhat();
			// print out exception  and exit
			std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(error);
			wcout << str << endl;
			exit(0);
		}
		break;
	}
	case 3:
	{
		iv = new byte[DES::KEYLENGTH];
		AutoSeededRandomPool prng;
		// generate random bytes key
		prng.GenerateBlock(iv, DES::DEFAULT_KEYLENGTH);
		break;
	}
	}

	if (option_input_iv != 2)
	{
		// store key to file
		StringSource ss(iv, DES::BLOCKSIZE, true, new FileSink("DES_iv.iv"));
		wcout << "iv has been saved to DES_iv.iv" << endl;
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
	std::wstring wplaintext = L"Welcome to the DES encryption and decryption!";
	wcout << "[+] Enter plaintext: ";
	std::getline(wcin, wplaintext);

	// random byte
	AutoSeededRandomPool prng;
	// key initiattion
	SecByteBlock key(DES::DEFAULT_KEYLENGTH);

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
		wcout << "Enter selection (1-6): ";

		wcin >> mode_option;
		if (mode_option < 1 || mode_option > 6)
		{
			wcout << "Input wrong options!\n";
		}
		else
		{
			break;
		}
	} while (1);

	key = key_selection();

	// not set iv for ECB mode
	if (mode_option != 1)
	{
		iv = iv_selection();
	}
	else
	{
		iv = NULL;
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
	total_time_encrypt = Estimation_En_De_cypt_Operation(plaintext, iv, key, ciphertext, mode_option, 0, loop);

	total_time_decrypt = Estimation_En_De_cypt_Operation(recovered, iv, key, ciphertext, mode_option, 1, loop);

	string mode_str[] = {"ECB", "CBC", "CBC CTS", "CFB", "CTR", "OFB"};
	wcout << endl;
	wcout << "[+] Estimation result" << endl;
	show_result(key, iv, DES::BLOCKSIZE, ciphertext, recovered, total_time_encrypt, total_time_decrypt, mode_str[mode_option - 1]);
	return 0;
}
