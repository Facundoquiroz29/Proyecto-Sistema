#include "systeminformation.h"
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
using namespace std;


SystemInformation::SystemInformation() {}

std::string SystemInformation::exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("_popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string SystemInformation::getOS()
{
    return exec("ver");
}

std::string SystemInformation::getCPU()
{
    return exec("wmic cpu get name /value");
}

std::string SystemInformation::getRAM()
{
    std::string output = exec("wmic computersystem get totalphysicalmemory /value");
    int pos = output.find('=');
    if (pos == NULL) return "N/A";

    std::string rawValue = output.substr(pos + 1);

    // LIMPIEZA MANUAL (Más segura para evitar errores de iteradores)
    std::string cleanValue = "";
    for (char c : rawValue) {
        if (isdigit(c)) { // Solo nos quedamos con los números
            cleanValue += c;
        }
    }

    if (cleanValue.empty()) return "0 GB";

    try {
        unsigned long long bytes = std::stoull(cleanValue);
        // El cálculo: Bytes / (1024^3)
        double gb = static_cast<double>(bytes) / 1073741824.0;

        char buffer[20];
        sprintf(buffer, "%.1f GB", gb);
        return std::string(buffer);
    } catch (...) {
        return "Error Conv.";
    }
}

std::string SystemInformation::getHostname()
{
    return exec("hostname");
}
