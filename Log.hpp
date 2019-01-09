#pragma once

/*
Use it by including this header in every file required, and in your main function start a new log.

    Logger::startLog("Log.txt");

Use the various error levels by naming them and simply passing the info and what you want to output.

    Logger::log(ERROR, "Something went wrong.");
*/

// For the unique pointers.
#include <memory>
// Filestream.
#include <fstream>
// String class for names and parameters passed around.
#include <string>

#define ERROR Logger::Level::Error
#define INFO Logger::Level::Info
#define DEBUG Logger::Level::Debug

namespace Logger {
    // Severity level enum.
    enum class Level {
        Error,
        Info,
        Debug
    };

    // Initialize the log.
    void startLog(const std::string& filepath);

    // Log a message.
    void log(Level s, const std::string& msg);

    // Logging class.
    class Log {
    public:
        Log(const std::string& filepath);
        void addLog(Level s, const std::string& msg);
        ~Log();
    private:
        // File for logging.
        std::ofstream m_logfile;
        std::string levels[3] = {"Error", "Info", "Debug"};
    };
}