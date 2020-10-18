#include <EngineUtils/FileUtils.hpp>

std::string EngineUtils::loadAsString(std::string_view path) {
    std::ifstream file;
    std::stringstream result;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(path.data());
        result << file.rdbuf();
        file.close();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR: Could not find or load file " << path << std::endl;
    }
    
    return result.str();
}