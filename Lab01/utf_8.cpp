#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>
#include<locale>
#include<codecvt>
using namespace std;
std::wstring s2ws(const std::string &str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring &wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}
int main()
{
    _setmode(_fileno(stdout), _O_U8TEXT); //needed for output
    _setmode(_fileno(stdin), _O_U8TEXT);  //needed for input

    std::wcout << L"Nhập tên của bạn: ";
    std::wstring name;
    std::getline(std::wcin, name);
    string a = "hello";
    wstring b = L"nguyễn văn tài";
    std::wcout << L"Xin chào, " << name << L"\n";
    std::wcout << a.c_str() << endl;
    a = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(b);
    wcout << b << endl;
    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(a);
    wcout << str << endl;

}