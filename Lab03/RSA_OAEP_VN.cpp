// Sample.cpp

#include "cryptopp/rsa.h"
using CryptoPP::Integer;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSA;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;

#include "cryptopp/sha.h"
using CryptoPP::SHA512;

#include "cryptopp/filters.h"
using CryptoPP::PK_DecryptorFilter;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

#include "cryptopp/files.h"
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include "cryptopp/queue.h" // using for load function
using CryptoPP::ByteQueue;

#include "cryptopp/cryptlib.h"
using CryptoPP::BufferedTransformation;
using CryptoPP::DecodingResult;
using CryptoPP::Exception;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

#include "cryptopp/cryptlib.h"
using CryptoPP::DecodingResult;
using CryptoPP::Exception;

#include <string>
using std::string;
using std::wstring;

#include <exception>
using std::exception;

#include <fstream>
#include <ctime>

#include <iostream>
using std::cerr;
using std::endl;
using std::wcin;
using std::wcout;
/* Convert to hex */
#include <cryptopp/hex.h>
using CryptoPP::HexDecoder;
using CryptoPP::HexEncoder;

#include <assert.h>

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

/* Integer convert */
#include <sstream>
using std::ostringstream;

/* Vietnames convert function def*/
wstring string_to_wstring(const std::string &str);
string wstring_to_string(const std::wstring &str);
wstring integer_to_wstring(const CryptoPP::Integer &t);
string wstring_hex_to_string(wstring wstr);

void Print_Option();
bool Input_Key(RSA::PrivateKey &priKey, RSA::PublicKey &pubKey, int option);
bool Input_str(string &plaintext, wstring type, int option);
bool Input_Plaintext(string &plaintext);
void LoadPrivateKey(const string &filename, RSA::PrivateKey &key);
void LoadPublicKey(const string &filename, RSA::PublicKey &key);
void Load(const string &filename, BufferedTransformation &bt);
void PrintKey(RSA::PrivateKey, RSA::PublicKey);
void Encryption();
void Decryption();

int main(int argc, char *argv[])
{
    try
    {
/*Set mode support Vietnamese*/
#ifdef __linux__
        setlocale(LC_ALL, "");
#elif _WIN32
        _setmode(_fileno(stdin), _O_U16TEXT);
        _setmode(_fileno(stdout), _O_U16TEXT);
#else
#endif
        wcout << "~Welcome to RSA encryption and decryption~\n";
        // RSA key
        do

        {
            wcout << endl;
            wcout << "[1] Encryption\n";
            wcout << "[2] Decryption\n";
            wcout << "[3] Exit\n";
            wcout << "Enter option: ";
            int option;
            wcin >> option;
            if (option == 1)
            {
                Encryption();
            }
            else if (option == 2)
            {
                Decryption();
            }
            else if (option == 3)
            {
                break;
            }
            else
            {
                wcout << "Enter invalid option!" << endl;
            }
        } while (1);
        return 0;
    }
    catch (CryptoPP::Exception &e)
    {
        cerr << "Caught Exception..." << endl;
        cerr << e.what() << endl;
    }
    return 0;
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

// convert string to char array and append '.'
char *string_to_char_array(string str)
{
    char *char_array = new char[str.length() + 1];
    for (long long i = 0; i < str.length(); i++)
    {
        char_array[i] = str[i];
    }

    char_array[str.length()] = str[str.length() - 1] != '.' ? '.' : '\0';
    char_array[str.length() + 1] = '\0';

    return char_array;
}

void Print_Option(int section)
{
    if (section == 0)
    {
        wcout << endl;
        wcout << "[+] Key Receive:\n";
        wcout << "[1] Default key\n";
        wcout << "[2] Input Key from keyboard\n";
        wcout << "[3] Key from file\n";
        wcout << "[4] Random Key\n";
        wcout << "Enter option: ";
    }
    else if (section == 1)
    {
        wcout << endl;
        wcout << "[+] Plaintext Receive:\n";
        wcout << "[1] Plaintext from file\n";
        wcout << "[2] Plaintext from keyboard\n";
        wcout << "Enter opiton: ";
    }
    else if (section == 2)
    {
        wcout << endl;
        wcout << "[+] Ciphertext Receive:\n";
        wcout << "[1] Ciphertext from file\n";
        wcout << "[2] Ciphertext from keyboard\n";
        wcout << "Enter option: ";
    }
    else
    {
    }
}

Integer Input_Integer_From_KeyBoard(wstring type)
{
    wcout << "Enter " << type << ": ";
    
    #ifdef __linux__
        __fpurge(stdin);
#elif _WIN32
        fflush(stdin);
#else
#endif

    wstring input;
    
    
    getline(wcin, input);

    Integer integer(string_to_char_array(wstring_to_string(input)));
    return integer;
    ;
}

bool Input_Key(RSA::PrivateKey &priKey, RSA::PublicKey &pubKey, int option)
{
    if (option == 1 || option == 2)
    {
        // Set default modulo in code
        Integer n("4846410981144595834051566307490793697381343896224710423128515628951343458217231117432037874252600232840996183552970048297986488188077212226244686792678057510734086278546352866101187776283926699092190643468913702315967984564867051913961835489436793116464418031424835218880235184075752435084079040373932656542050632709779700538736237481952776369994823896881762875619376785125692612493931034480972363873195673281720181111896083663492650028098192854319428842352323208728652701451400150446427548974361249198594957458941121363996876490135995581669451857102327529952024078156827071590404325636682681842593578649382641424451537687916117096935551152203607652535408251516355166534540329966091264741785402970205399012778046815242736858622808551846612925327734555015748053192087589853558127112227541329078614945997264668978146192449975991441935360429784773924913605717344705581056878453562513827359652499732347965341757590409672383219933.");

        // Set default p,q
        Integer p("2070041337034921162083149572169930905375665857341387930631606457952881812959985939315117403539808215905534338350286302749873463300394964715420809343362978363357871095075579915306717299023788102891659001126038509582944578243570793780825890549031768986988853311731150342900713127939250537300968543513429024102417337016382187107144610745591752463844642204732806600050931639014658798658617988045429549118623796934485365988721720080167283164595860423130919045683404661.");
        Integer q("2341214590471165020926482158414312505571165874936027838531308736896735499739752709215989928389807974542676541607320997432574075625871271930319215562429145521236547166843162573292918248089821014141403708229086442238417585194753085774976029937581092301900807950973951749913072766389992103094819480113474772526791149579575731620125983708319098785757574178955909279022659413859729915918259266841253082118955820267540000743077430464879671865311320495317535490933898953.");

        // Set default exponential
        Integer e("17.");

        // Set default private exponnential
        Integer d("427624498336287867710432321249187679180706814372768566746633731966295011019167451538120988904641197015382016195850298379234101898947989314080413540530416839182419377518795841126575392025052355802252115600198267851408939814547092815937809013773834686746860414537485460489432516241978156036830503562405822636063291121451150047535550366054656738528955049724861430201709716334619936396523326571850502694693735877798839509873183852661116178949840545969361368442852047439770303583410055950305513387363338669273225751311060488330736615339883783699776764058381964735514732054054157116156247928453860786149141139060976673440675272955693103958211401697181812258202166334145218653787221347405396448638751220731021682345596287551306542957710212181828111419273014049505096437202143586329840984203718887513308326630530741184861397388302669222136689944800311504205181091298247176597618508370216061312568304656822181602426983113688449933793.");

        if (option == 2)
        {
            n = Input_Integer_From_KeyBoard(L"Modulo");
            p = Input_Integer_From_KeyBoard(L"Prime p");
            q = Input_Integer_From_KeyBoard(L"Prime q");
            e = Input_Integer_From_KeyBoard(L"Public exponential");
            d = Input_Integer_From_KeyBoard(L"Private exponential");
        }
        priKey.SetModulus(n);
        priKey.SetPrime1(p);
        priKey.SetPrime2(q);
        priKey.SetPublicExponent(e);
        priKey.SetPrivateExponent(d);

        priKey.SetModPrime1PrivateExponent(d % (p - 1));
        priKey.SetModPrime2PrivateExponent(d % (q - 1));
        priKey.SetMultiplicativeInverseOfPrime2ModPrime1(q.InverseMod(p));
        // Create public key from private key

        pubKey = RSA::PublicKey(priKey);
    }
    else if (option == 4)
    {
        // Generate keys
        AutoSeededRandomPool rng;
        InvertibleRSAFunction parameters;
        parameters.GenerateRandomWithKeySize(rng, 3072);

        priKey = RSA::PrivateKey(parameters);
        pubKey = RSA::PublicKey(parameters);
    }
    else if (option == 3)
    {
        LoadPublicKey(".\\rsa-public.key", pubKey);
        LoadPrivateKey(".\\rsa-private.key", priKey);
        return true;
    }
    else
    {
        wcout << "Enter invalid option\n";
        return false;
    }

    return true;
}

void LoadPrivateKey(const string &filename, RSA::PrivateKey &key)
{
    ByteQueue queue;
    Load(filename, queue);
    key.Load(queue);
}

void LoadPublicKey(const string &filename, RSA::PublicKey &key)
{

    ByteQueue queue;
    Load(filename, queue);
    key.Load(queue);
}

void Load(const string &filename, BufferedTransformation &bt)
{
    FileSource file(filename.c_str(), true /*pumpAll*/);
    file.TransferTo(bt);
    bt.MessageEnd();
}

void PrintKey(RSA::PrivateKey privateKey, RSA::PublicKey publicKey)

{
    wcout << endl;
    wcout << "RSA parameters:" << endl;
    wcout << "Public modulo n=" << integer_to_wstring(publicKey.GetModulus()) << endl
          << endl;
    wcout << "Public key e=" << integer_to_wstring(publicKey.GetPublicExponent()) << endl
          << endl;
    wcout << "Private prime number p=" << integer_to_wstring(privateKey.GetPrime1()) << endl
          << endl;
    wcout << "Private prime number q=" << integer_to_wstring(privateKey.GetPrime2()) << endl
          << endl;
    wcout << "Secret key d=" << integer_to_wstring(privateKey.GetPrivateExponent()) << endl
          << endl;
}

void Encryption()
{

    AutoSeededRandomPool rng;
    RSA::PrivateKey privateKey;
    RSA::PublicKey publicKey;

    string plaintext, recovered, ciphertext;
    int section = 0;
    do
    {
        Print_Option(section);
        int option;
        wcin >> option;
        if (section == 0)
        {
            if (Input_Key(privateKey, publicKey, option))
            {
                section += 1;
                continue;
            }
        }
        if (section == 1)
        {
            if (Input_str(plaintext, L"plaintext", option))
            {
                section += 1;
                break;
            }
        }
    } while (1);
    wcout << "Plaintext: " << string_to_wstring(plaintext) << endl;
    // Encryption
    PrintKey(privateKey, publicKey);

    RSAES_OAEP_SHA_Encryptor e(publicKey); // RSAES_PKCS1v15_Decryptor

    int loop = 10000;
    int start_s = clock();
    while (loop--)
    {
        ciphertext.clear();
        StringSource(plaintext, true,
                     new PK_EncryptorFilter(rng, e,
                                            new StringSink(ciphertext)) // PK_EncryptorFilter
        );                                                              // StringSource
    }
    int stop_s = clock();
    double etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    string encoded;
    encoded.clear();
    StringSource(ciphertext, true,
                 new HexEncoder(new StringSink(encoded)));

    wcout << endl;
    wcout << "[+] Ciphertext: " << string_to_wstring(encoded) << endl;
    wcout << "Total excecution time for 10000 loop: " << etime << "ms" << endl;
    wcout << "Average execution time for 10000 loop: " << etime / 10000 << "ms" << endl;
}

void Decryption()
{
    RSA::PrivateKey privateKey;
    AutoSeededRandomPool rng;
    RSA::PublicKey publicKey;

    string recovered, ciphertext;
    int section = 0;
    do
    {
        Print_Option(section);
        int option;
        wcin >> option;
        if (section == 0)
        {
            if (Input_Key(privateKey, publicKey, option))
            {
                section += 2;
                continue;
            }
        }
        if (section == 2)
        {
            if (Input_str(ciphertext, L"ciphertext", option))
            {
                section += 2;
                break;
            }
        }
    } while (1);
    // Decryption

    RSAES_OAEP_SHA_Decryptor d(privateKey);



    int loop = 10000;
    int start_s = clock();
    while (loop--)
    {
        recovered.clear();
        StringSource(ciphertext, true,
                     new PK_DecryptorFilter(rng, d,
                                            new StringSink(recovered)) // PK_EncryptorFilter
        );                                                             // StringSource
    }
    int stop_s = clock();
    double etime = (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000;
    // StringSource
    wcout << endl;
    wcout << "[+] Recover text: " << string_to_wstring(recovered) << endl;
    wcout << "Total excecution time for 10000 loop: " << etime << "ms" << endl;
    wcout << "Average execution time for 10000 loop: " << etime / 10000 << "ms" << endl;
}

bool Input_str(string &plaintext, wstring type, int option)

{
    if (option == 1)
    {
        wcout << endl;
        wcout << "[+] Enter " << type << " from file:\n";
        wcout << "Enter " << type << " file name: ";
        
        #ifdef __linux__
        __fpurge(stdin);
#elif _WIN32
        fflush(stdin);
#else
#endif

        wstring filename_wstr;
        getline(wcin, filename_wstr);
        string filename = wstring_to_string(filename_wstr);
        std::ifstream file;
        file.open(filename);
        if (!file.is_open())
        {
            wcout << L"File " << filename_wstr << L" không tồn tại" << endl;
            exit(0);
        }

        string plain;
        string line;
        while (file.good())
        {
            getline(file, line);
            plain += line;
        }
        if (wstring_to_string(type) == "ciphertext")
        {
            plain = wstring_hex_to_string(string_to_wstring(plain));
        }
        plaintext = plain;
    }

    else if (option == 2)
    {
        wcout << endl;
        wcout << "[+] Enter " << type << " from keyboard:\n";
        wcout << "Enter " << type << ": ";
        wstring w_plaintext;
        w_plaintext.clear();
        
        #ifdef __linux__
        __fpurge(stdin);
#elif _WIN32
        fflush(stdin);
#else
#endif

        getline(wcin, w_plaintext);
        if (wstring_to_string(type) == "ciphertext")
        {
            plaintext = wstring_hex_to_string(w_plaintext);
        }
        else
        {
            plaintext = wstring_to_string(w_plaintext);
        }
    }
    else
    {
        wcout << "Enter invalid option\n";
        return false;
    }
    return true;
}
