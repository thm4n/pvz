#include <inc/Logger.hpp>

namespace logger {
    void _error(const char* file, const char* func, const unsigned int line, const char* format, ...) {
        va_list args;
        time_t now;

        va_start(args, format);
        int size = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        if(size < 0)
            return;

        char* buffer = new char[size + 1];
        if(!buffer) 
            return;

        va_start(args, format);
        vsnprintf(buffer, size + 1, format, args);
        buffer[size] = '\0';
        va_end(args);

        char timestr[9] = {0};
        time(&now);
        strftime(timestr, sizeof(timestr), "%H:%M:%S", localtime(&now));
        timestr[8] = '\0';

        set(TermCmd::Bold);
        set(TermCmd::SetColor, TermColor::Red);
        fprintf(stdout, "[%s] - ERROR - %s:%s (%d) - %s\n", timestr, file, func, line, buffer);
        set(TermCmd::Reset);

        delete[] buffer;
    }

    void _warning(const char* file, const char* func, const unsigned int line, const char* format, ...) {
        va_list args;
        time_t now;

        va_start(args, format);
        int size = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        if(size < 0)
            return;

        char* buffer = new char[size + 1];
        if(!buffer) 
            return;

        va_start(args, format);
        vsnprintf(buffer, size + 1, format, args);
        buffer[size] = '\0';
        va_end(args);

        char timestr[9] = {0};
        time(&now);
        strftime(timestr, sizeof(timestr), "%H:%M:%S", localtime(&now));
        timestr[8] = '\0';
        
        set(TermCmd::Bold);
        set(TermCmd::SetColor, TermColor::Yellow);
        fprintf(stdout, "[%s] - WARN  - %s:%s (%d) - %s\n", timestr, file, func, line, buffer);
        set(TermCmd::Reset);
        
        delete[] buffer;
    }

    void _info(const char* file, const char* func, const unsigned int line, const char* format, ...) {
        va_list args;
        time_t now;

        va_start(args, format);
        int size = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        if(size < 0)
            return;

        char* buffer = new char[size + 1];
        if(!buffer) 
            return;

        va_start(args, format);
        vsnprintf(buffer, size + 1, format, args);
        buffer[size] = '\0';
        va_end(args);

        char timestr[9] = {0};
        time(&now);
        strftime(timestr, sizeof(timestr), "%H:%M:%S", localtime(&now));
        timestr[8] = '\0';

        set(TermCmd::SetColor, TermColor::Green);
        fprintf(stdout, "[%s] - INFO  - %s:%s (%d) - %s\n", timestr, file, func, line, buffer);
        set(TermCmd::Reset);
        
        delete[] buffer;
    }

    void _debug(const char* file, const char* func, const unsigned int line, const char* format, ...) {
        va_list args;
        time_t now;

        va_start(args, format);
        int size = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        if(size < 0)
            return;

        char* buffer = new char[size + 1];
        if(!buffer) 
            return;

        va_start(args, format);
        vsnprintf(buffer, size + 1, format, args);
        buffer[size] = '\0';
        va_end(args);

        char timestr[9] = {0};
        time(&now);
        strftime(timestr, sizeof(timestr), "%H:%M:%S", localtime(&now));
        timestr[8] = '\0';

        set(TermCmd::Bold);
        set(TermCmd::SetColor, TermColor::Blue);
        fprintf(stdout, "[%s] - DEBUG - %s:%s (%d) - %s\n", timestr, file, func, line, buffer);
        set(TermCmd::Reset);
        
        delete[] buffer;
    }

    void _fatal(const char* file, const char* func, const unsigned int line, const char* format, ...) {
        va_list args;
        time_t now;

        va_start(args, format);
        int size = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        if(size < 0)
            return;

        char* buffer = new char[size + 1];
        if(!buffer) 
            return;

        va_start(args, format);
        vsnprintf(buffer, size + 1, format, args);
        buffer[size] = '\0';
        va_end(args);

        char timestr[9] = {0};
        time(&now);
        strftime(timestr, sizeof(timestr), "%H:%M:%S", localtime(&now));
        timestr[8] = '\0';

        set(TermCmd::Bold);
        set(TermCmd::SetColor, TermColor::BG_Red);
        set(TermCmd::SetColor, TermColor::White);
        fprintf(stdout, "[%s] - FATAL - %s:%s (%d) - %s\n", timestr, file, func, line, buffer);
        set(TermCmd::Reset);
        
        delete[] buffer;
    }

    // set functions
    void set(const TermCmd cmd) {
        switch (cmd) {
            case TermCmd::Clear:
                std::cout << "\033[2J\033[H";
                break;
            case TermCmd::Bold:
                std::cout << "\033[1m";
                break;
            case TermCmd::Underline:
                std::cout << "\033[4m";
                break;
            case TermCmd::Reset:
                std::cout << "\033[0m";
                break;
            case TermCmd::MoveHome:
                std::cout << "\033[H";
                break;
            case TermCmd::HideCursor:
                std::cout << "\033[?25l";
                break;
            case TermCmd::ShowCursor:
                std::cout << "\033[?25h";
                break;
            case TermCmd::Move:
                warning("Move command requires int row and int column arguments");
                break;
            case TermCmd::SetColor:
                warning("SetColor command requires a TermColor color argument");
                break;
            default:
                error("Unknown command recieved");
                break;
        }
    }

    void set(const TermCmd cmd, int row, int col) {
        switch (cmd) {
        case TermCmd::Clear:
        case TermCmd::Bold:
        case TermCmd::Underline:
        case TermCmd::Reset:
        case TermCmd::MoveHome:
        case TermCmd::HideCursor:
        case TermCmd::ShowCursor:
        case TermCmd::SetColor:
            warning("only the Move TermCmd requires int row and int column arguments");
            break;
        case TermCmd::Move:
            std::cout << "\033[" << row << ";" << col << "H";
            break;
        default:
            error("Unknown command recieved");
            break;
        }
    }

    void set(const TermCmd cmd, const TermColor tc) {
        switch (cmd) {
        case TermCmd::Clear:
        case TermCmd::Bold:
        case TermCmd::Underline:
        case TermCmd::Reset:
        case TermCmd::MoveHome:
        case TermCmd::HideCursor:
        case TermCmd::ShowCursor:
        case TermCmd::Move:
            warning("only the TermCmd::SetColor command requires TermColor argument");
            break;
        case TermCmd::SetColor:
            std::cout << "\033[" << static_cast<int>(tc) << "m";
            break;
        default:
            error("Unknown command recieved");
            break;
        }
    }

};
