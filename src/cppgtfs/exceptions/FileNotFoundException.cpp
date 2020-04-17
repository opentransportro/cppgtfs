#include <cppgtfs/exceptions/FileNotFoundException.h>
#include <sstream>

namespace cppgtfs::exceptions
{
    FileNotFoundException::FileNotFoundException(std::string file_name) :
        _msg("File not found"),
        _file_name(file_name)
    {
    }
    const char* FileNotFoundException::what() const noexcept
    {
        std::stringstream ss;
        ss << _file_name << " : " << _msg;
        _what_msg = ss.str();
        return _what_msg.c_str();
    }
    std::string FileNotFoundException::getFileName() const noexcept
    {
        return _file_name;
    }
}    // namespace cppgtfs::exceptions
