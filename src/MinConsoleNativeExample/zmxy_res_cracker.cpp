#include "MinConsoleNative.hpp"
#include <vector>
using namespace std;

//造梦西游版本
enum class ZMXY_Version
{
    Unknown = 0,            //未知
    yongchuangdifu = 2,     //勇闯地府
    zaixutianting = 3,      //再续天庭
};

enum class CrackMode
{
    Decode = 0,
    Encode = 1,
};

#define DEFAULT_LEN 16777216

static int pivot = 0;
static int end = 0;

int GetPivot()
{
    return ::pivot;
}

int GetEnd()
{
    return ::end;
}

struct ByteData
{
private:
    BYTE* data = nullptr;
    int capacity = 0;
    int position = 0;

public:
    ByteData()
    {
        allocateMemory(DEFAULT_LEN);
    }

    ~ByteData()
    {
        delete[] data;
    }

    void write(BYTE byte_to_save)
    {
        if (position >= capacity)
        {
            allocateMemory(capacity * 2);
        }
        data[position++] = byte_to_save;
    }

    BYTE* getData()
    {
        return data;
    }

    int getByteLen()
    {
        return position * sizeof(BYTE);
    }

    void encode()
    {
        switchHeader(GetEnd() - GetPivot());
    }

    void decode()
    {
        switchHeader(GetPivot());
    }

private:
    void allocateMemory(int len)
    {
        if (capacity >= len) return;

        if (capacity > 0)
        {
            BYTE* buf = data;
            data = new BYTE[len];
            memcpy(data, buf, this->capacity);
            delete[] buf;
        }
        else
        {
            data = new BYTE[len];
        }

        this->capacity = len;
    }

    void switchHeader(int pivot)
    {
        BYTE* newData = new BYTE[capacity];
        int index = 0;
        for (int i = pivot; i < GetEnd(); i++)
        {
            newData[index++] = data[i];
        }
        for (int i = 0; i < pivot; i++)
        {
            newData[index++] = data[i];
        }
        while (index < position)
        {
            newData[index] = data[index];
            index++;
        }
        delete[] data;
        this->data = newData;
    }
};

bool ProcessFile(const wstring& path, CrackMode cmode, const wstring& outputPath)
{
    ByteData dataBuf;
    vector<MinConsoleNative::byte> bytes = File::ReadAllBytes(path);
    for (const auto& byte : bytes)
    {
        dataBuf.write(byte);
    }

    if (cmode == CrackMode::Decode) dataBuf.decode();
    else if (cmode == CrackMode::Encode) dataBuf.encode();

    std::vector<MinConsoleNative::byte> output_bytes;
    for (size_t i = 0; i < dataBuf.getByteLen(); i++)
    {
        output_bytes.push_back(dataBuf.getData()[i]);
    }
    //如果不存在就创建
    if (!File::Exists(outputPath))
    {
        File::Creat(outputPath);
    }
    return File::WriteAllBytes(outputPath, output_bytes);
}

int main()
{
    wstring crackFilePath = FileDialog::Open(nullptr);

    Database database;
    database.SetSavePath(crackFilePath);

    //config:
    ZMXY_Version zmVer;
    wstring in_res;
    wstring out_res;

    int version = database.GetInt(L"ver", 0);
    switch (version)
    {
    case 2:
        zmVer = ZMXY_Version::yongchuangdifu;
        ::pivot = 96;
        ::end = 165;
        break;
    case 3:
        zmVer = ZMXY_Version::zaixutianting;
        ::pivot = 200;
        ::end = 275;
        break;
    default:
        zmVer = ZMXY_Version::Unknown;
        break;
    }

    in_res = database.GetString(L"in_res", L"");
    out_res = database.GetString(L"out_res", L"");

    //read config successful:
    if (zmVer != ZMXY_Version::Unknown && in_res != L"" && out_res != L"")
    {
        wstring workDir = File::GetFileDir(crackFilePath);
        wstring res_folder = File::Combine(workDir, in_res);
        wstring output_folder = File::Combine(workDir, out_res);

        //如果不存在就创建
        if (!File::Exists(output_folder))
        {
            File::Creat(output_folder, FileMode::Directory);
        }

        vector<wstring> swfNames = File::GetFileNamesWithExtension(res_folder, L".swf");
        for (const wstring& item : swfNames)
        {
            wstring output_path = output_folder + item;
            wstring input_path = res_folder + item;

            bool handle_suc = ProcessFile(input_path, CrackMode::Decode, output_path);
            if (handle_suc)
            {
                console.WriteLine(L"Decode Successful!" + item);
            }
            else
            {
                console.WriteLine(L"Decode Error!", { 255, 0, 0 });
            }
        }

        int debug = 0;
    }

    system("pause");
    return 0;
}