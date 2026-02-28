#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H
#include <string>
#include <vector>

class SystemInformation
{
private:
    std::string exec(const char* cmd);
public:
    SystemInformation();
    std::string getOS();
    std::string getCPU();
    std::string getRAM();
    std::string getHostname();

};

#endif // SYSTEMINFORMATION_H
