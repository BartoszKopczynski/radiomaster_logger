#include "CSVLogger.hpp"

CsvLogger::CsvLogger(const std::string& path) {
    file_.open(path);
    file_ << "time_ms,axis,value\n";
}

CsvLogger::~CsvLogger() {
    file_.close();
}

void CsvLogger::log(const StickEvent& evt) {
    file_ << evt.time_ms << ","
          << static_cast<int>(evt.axis) << ","
          << evt.value << "\n";
}

