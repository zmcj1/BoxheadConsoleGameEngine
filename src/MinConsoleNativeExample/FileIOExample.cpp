#include "MinConsoleNative.hpp"
#include <vector>
using namespace std;

int main()
{
    vector<MinConsoleNative::byte> bytes;
    bytes.push_back('1');
    bytes.push_back('2');
    bytes.push_back('0');

    File::WriteAllBytes(L"../../res/io_test.txt", bytes);

    bytes = File::ReadAllBytes(L"../../res/io_test.txt");

    return 0;
}