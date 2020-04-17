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
        WriteException(std::string msg, std::string file_name) :
            _msg(msg), _file_name(file_name) {}

        WriteException(std::string msg) :
            _msg(msg), _file_name("?") {}

        ~WriteException() throw() {}

        virtual const char* what() const throw()
        {
            std::stringstream ss;
            ss << _file_name << ":";
            ss << " " << _msg;
            _what_msg = ss.str();
            return _what_msg.c_str();
        }

    private:
        mutable std::string _what_msg;
        std::string _msg;
        std::string _file_name;
    };
}
#endif    //CPPGTFS_WRITEEXCEPTION_H
