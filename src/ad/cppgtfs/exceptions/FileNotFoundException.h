#ifndef CPPGTFS_FILENOTFOUNDEXCEPTION_H
#define CPPGTFS_FILENOTFOUNDEXCEPTION_H

#include <exception>
#include <string>

namespace ad::cppgtfs::exceptions
{
    class FileNotFoundException : public std::exception
    {
    public:
        FileNotFoundException(std::string file_name);

        ~FileNotFoundException() noexcept = default;

        const char* what() const noexcept override;

        std::string getFileName() const noexcept;

    private:
        mutable std::string _what_msg;
        std::string _msg;
        std::string _file_name;
    };
}

#endif    //CPPGTFS_FILENOTFOUNDEXCEPTION_H
