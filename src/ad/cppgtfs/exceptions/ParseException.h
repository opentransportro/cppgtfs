#ifndef CPPGTFS_PARSEEXCEPTION_H
#define CPPGTFS_PARSEEXCEPTION_H

#include <exception>
#include <string>

namespace ad::cppgtfs::exceptions
{
    class ParseException : public std::exception
    {
    public:
        ParseException(std::string msg, std::string field_name, int64_t line, std::string file_name);

        ParseException(std::string msg, std::string field_name, int64_t line);

        ~ParseException() noexcept = default;

        const char* what() const noexcept override;

        uint64_t getLine() const noexcept;

        void setFileName(const std::string& fn);

    private:
        mutable std::string _what_msg;
        std::string _msg;
        std::string _field_name;
        int64_t _line;
        std::string _file_name;
    };
}
#endif    //CPPGTFS_PARSEEXCEPTION_H
