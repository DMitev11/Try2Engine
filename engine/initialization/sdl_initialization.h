#pragma once
#include <vector>
#include <unordered_map>
#include <string>
class SDLInitialization  
{
public:
    SDLInitialization() = delete;
    ~SDLInitialization() = default;
 
    static bool init(std::vector<uint32_t> initFlags, std::unordered_map<const char*, const char*> hintFlags);
};