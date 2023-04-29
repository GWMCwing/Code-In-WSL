#include <windows.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <stdexcept>
#include <memory>
#include <cstdio>

std::string getWSLPath(std::string pathMS) {
    const std::string msInWSLPath = "/mnt";
    if (pathMS.length() < 3) {
        std::cout << "Path too short." << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        std::cin.get();
        exit(2);
    }
    pathMS[0] += 32;
    pathMS.erase(1, 1);
    for (int i = 0;i < pathMS.length();++i) {
        if (pathMS[i] == '\\') {
            pathMS[i] = '/';
            continue;
        }
        if (pathMS[i] == ' ') {
            pathMS.insert(i, "\\");
            ++i;
        }
    }
    return msInWSLPath + "/" + pathMS;
}

const std::string getWSLDistro(const int& argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-d") == 0) {
            return "-d " + std::string(argv[i + 1]);
        }
    }
    return "";
}


//From https://stackoverflow.com/a/478960
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc == 1) return 1;
    for (int i = 0; i < argc; ++i) {
        std::cout << "Arg " << i << ": " << argv[i] << std::endl;
    }
    const std::string wslDistro = getWSLDistro(argc, argv);
    std::cout << "Distro: " << (wslDistro.length() ? wslDistro : "None") << std::endl;
    const std::string wslPath = getWSLPath(argv[(wslDistro.length() == 0) ? 1 : 3]);
    std::cout << "WSL Path: " << wslPath << std::endl;
    const std::string WSL_CMD = "wsl " + wslDistro + " -e sh -c \"cd " + wslPath + " && code .\"";
    std::cout << "Command: " << WSL_CMD << std::endl;
    const std::string output = exec(WSL_CMD.c_str());
    if (output.length() != 0) {
        std::cout << output << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        std::cin.get();
        exit(1);
    }
    return 0;
}