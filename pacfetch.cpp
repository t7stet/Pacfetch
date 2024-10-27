#include <iostream>
#include <cstdlib>
#include <string>

//Здрасте тем кто смотрит этот код :p

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "popen() failed!";
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

int main() {
    std::string version = exec("pacman -V | head -n 2 | tail -n 1 | awk '{print $3}' | tail -c+2");
    std::string totalPackages = exec("pacman -Q | wc -l");
    std::string explicitPackages = exec("pacman -Qe | wc -l");
    std::string availableUpdates = exec("pacman -Qu | wc -l");

    std::cout << "   .--.                │ \033[0;33m Версия\033[0;39m: " << version;
    std::cout << "  / _.-' .-.  .-.  .-. │ \033[0;32m Пакетов\033[0;39m: " << totalPackages;
    std::cout << "  \\  '-. '-'  '-'  '-' │ \033[0;34m Эксплицитные пакеты\033[0;39m: " << explicitPackages;
    std::cout << "   '--'                │ \033[0;31m Доступных обновлений\033[0;39m: " << availableUpdates << "\n";
    return 0;
}
