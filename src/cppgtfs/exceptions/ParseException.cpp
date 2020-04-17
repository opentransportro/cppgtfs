#include <cppgtfs/exceptions/ParseException.h>

#include <sstream>

namespace cppgtfs::exceptions
{
    ParseException::ParseException(std::string msg, std::string field_name, int64_t line, std::string file_name) :
        _msg(msg),
        _field_name(field_name),
        _line(line),
        _file_name(file_name)
    {
    }
    ParseException::ParseException(std::string msg, std::string field_name, int64_t line) :
        _msg(msg), _field_name(field_name), _line(line), _file_name("?")
    {
    }

    const char* ParseException::what() const noexcept
    {
        std::stringstream ss;
        ss << _file_name << ":";
        if (_line > -1) ss << _line << ":";
        if (!_field_name.empty()) ss << " in field '" << _field_name << "',";
        ss << " " << _msg;
        _what_msg = ss.str();
        return _what_msg.c_str();
    }

    uint64_t ParseException::getLine() const noexcept
    {
        return _line;
    }
    void ParseException::setFileName(const std::string& fn)
    {
        _file_name = fn;
    }
}