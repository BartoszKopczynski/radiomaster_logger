#pragma once
#include <fstream>
#include "JoystickReader.hpp"

class CsvLogger {
public:
    CsvLogger(const std::string& path);
    ~CsvLogger();

    void log(const StickEvent& evt);

private:
    std::ofstream file_;
};

