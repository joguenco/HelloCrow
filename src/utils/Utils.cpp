#include "Utils.hpp"

namespace Utils
{
    std::string GetEnv(std::string_view varName, std::string_view defaultValue)
    {
        const char* val = std::getenv(varName.data());
        
        printf("Environment variable: %s=%s\n", varName.data(), val ? val : "NULL");
        
        return (val && val[0] != '\0') ? std::string(val) : std::string(defaultValue);
    }
} // namespace Utils
