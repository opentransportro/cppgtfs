#include <cppgtfs/exceptions/WriteException.h>

namespace cppgtfs::exceptions
{
    WriteException::WriteException(std::string msg, std::string file_name) :
        _msg(msg), _file_name(file_name) {}
    WriteException::WriteException(std::string msg) :
        _msg(msg), _file_name("?") {}
    const char* WriteException::what() const noexcept
    {
        std::stringstream ss;
        ss << _file_name << ":";
        ss << " " << _msg;
        _what_msg = ss.str();
        return _what_msg.c_str();
    }
}