#include <EngineUtils/FileUtils.hpp>

int main() {
    std::cout << EngineUtils::loadAsString("test.txt") << std::endl;
}