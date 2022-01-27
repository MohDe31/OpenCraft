#pragma once

#include <string>

class Shader 
{
    public:
        unsigned int ID;

        Shader(const char* vertPath, const char* fragPath);
        Shader();

        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, float* value) const;
};