#ifndef INCLUDED_EngineUtils_FileUtils_hpp
#define INCLUDED_EngineUtils_FileUtils_hpp

#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <iostream>

namespace EngineUtils {
    std::string loadAsString(std::string_view path);
}

#endif