#include <iostream>
#include "systeminformation.h"
using namespace std;

int main()
{
    SystemInformation info;

    cout << "--- Datos del Sistema (C++ Puro) ---" << endl;
    cout << "OS: " << info.getOS()<< endl;
    cout << "Hostname: " << info.getHostname() << endl;
    cout << "CPU: " << info.getCPU() << endl;
    cout << "RAM: " << info.getRAM() << endl;
    cout << endl;

    return 0;
}
