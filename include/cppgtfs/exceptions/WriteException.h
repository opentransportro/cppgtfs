#ifndef CPPGTFS_WRITEEXCEPTION_H
#define CPPGTFS_WRITEEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>

namespace cppgtfs::exceptions
{
    class WriteException : public std::exception
    {
    public:
        WriteException(std::string msg, std::string file_name);

        WriteException(std::string msg);

        ~WriteException() noexcept = default;

        virtual const char* what() const noexcept;

    private:
        mutable std::string _what_msg;
        std::string _msg;
        std::string _file_name;
    };
}    // namespace cppgtfs::exceptions
#endif    //CPPGTFS_WRITEEXCEPTION_H
