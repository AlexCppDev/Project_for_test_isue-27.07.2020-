#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <iostream>
#include <stdint.h>
#include <string>
#include <Winsock2.h>
#include <Iphlpapi.h>
#include <conio.h>

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "IPHlpApi.Lib")
bool CheckAddress(char* ip_)
{
    int dots = 0,
        num = 0;
    char* buff;
    buff = new char[3];
    for (int i = 0; ip_[i] != '\0'; i++)
    {
        if (ip_[i] <= '9' && ip_[i] >= '0')
        {
            if (num > 3) return false;

            buff[num++] = ip_[i];

        }
        else
            if (ip_[i] == '.')
            {
                if (atoi(buff) > 255)

                    return false;
                if (num == 0)

                    return false;
                num = 0;
                dots++;
                delete[]buff;
                buff = new char[3];
            }
            else return false;

    }
    if (dots != 3)
        return false;
    if (num == 0 || num > 3)
        return false;
    return true;
}
std::string NetworkCalc()
{
    std::string str;
    char ip_[20];
    char mask_[20];
    bool flag_ip = true;
    bool flag_mask = true;

    std::cout << "Enter IP: " << std::endl;
    std::cin >> ip_;
    std::cout << "Enter Mask: " << std::endl;
    std::cin >> mask_;

    if (CheckAddress(ip_) != true)
    {
        std::cout << "error" << std::endl;
        flag_ip = false;
    }

    if (CheckAddress(mask_) != true)
    {
        std::cout << "error" << std::endl;
        flag_mask = false;
    }

    if (flag_ip != false && flag_mask != false)
    {
        uint32_t ipaddress = ntohl(inet_addr(ip_));
        uint32_t subnetmask = ntohl(inet_addr(mask_));
        uint32_t broadcast = (ipaddress & subnetmask) | ~subnetmask;

        uint32_t bytes_broadcast = broadcast;
        struct in_addr ip_broad { htons(bytes_broadcast) };
        ip_broad.s_addr;
        ip_broad.S_un.S_addr = bytes_broadcast;
        std::cout << "Result: " << inet_ntoa(ip_broad) << std::endl;
        str = inet_ntoa(ip_broad);

    }
    else
    {
        std::cout << "Fatal error" << std::endl;
    }
    return str;
}

uint16_t get_value_for_Bytes_changer()
{
    std::cout << "Enter value for change 1 and 2 byte (only hex): 0x";
    uint16_t value_for_Bytes_changer;
    std::cin >> std::hex >> value_for_Bytes_changer;
    return value_for_Bytes_changer;
}
uint32_t Bytes_changer32 (uint32_t ui32)
{
    ui32 = (ui32 & 0x00FF00FF) << 8 | (ui32 & 0xFF00FF00) >> 8;
    ui32 = (ui32 & 0x0000FFFF) << 16 | (ui32 & 0xFFFF0000) >> 16;
    std::cout << std::hex << ui32 << std::endl;
    return ui32;
}

uint16_t Bytes_changer16 (uint16_t ui16)
{
    ui16 = (((ui16 << 8) & 0xFFFF) | ((ui16 >> 8) & 0xFFFF));
     

    std::cout << std::hex << ui16 << std::endl;
    return ui16;
}
uint64_t get_value_for_PowCalc()
{
    std::cout << "Enter pow value: " <<std::endl;
    int pow_value;
    std::cin >> pow_value;
    return pow_value;
}

DWORD PowCalc(int  pow_value)
{

    return  1 << pow_value;
};



int main(int argc, char* argv[])
{

   
     Bytes_changer16(get_value_for_Bytes_changer());
     _getch();
     PowCalc(get_value_for_PowCalc());
     _getch();
     NetworkCalc();
     _getch();
  

   
}






