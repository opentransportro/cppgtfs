// Copyright 2018, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <csv/CsvWriter.h>

using std::remove;

namespace csv
{

    CsvWriter::CsvWriter(std::ostream* str, HeaderList headers) :
        _stream(str), _headers(std::move(headers)), _delim(',') {}


    bool CsvWriter::writeDouble(double d)
    {
        std::ostringstream str;
        str << std::setprecision(11) << d;
        writeRawString(str.str());

        return true;
    }


    void CsvWriter::skip() { _curL.push_back(""); }


    bool CsvWriter::writeString(const std::string& str)
    {
        if (str.find(_delim) != std::string::npos || str.find('"') != std::string::npos) {
            writeRawString("\"" + escStr(str) + "\"");
        } else {
            writeRawString(str);
        }

        return true;
    }


    std::string CsvWriter::escStr(const std::string& str)
    {
        std::stringstream ret;
        for (char i : str) {
            if (i == '\"') {
                ret << "\"\"";
            } else {
                ret << i;
            }
        }

        return ret.str();
    }


    bool CsvWriter::writeRawString(const std::string& str)
    {
        _curL.push_back(str);
        return true;
    }


    bool CsvWriter::writeInt(int i)
    {
        std::ostringstream str;
        str << i;
        writeRawString(str.str());
        return true;
    }


    void CsvWriter::flushLine()
    {
        if (!_hWritten) {
            _hWritten = true;
            writeStrArr(_headers);
        }

        writeStrArr(_curL);
        _curL.clear();
    }


    void CsvWriter::writeStrArr(const std::vector<std::string>& arr)
    {
        if (arr.empty()) { return; }
        bool first = false;
        for (const auto& str : arr) {
            if (first) { (*_stream) << _delim; }
            first = true;
            (*_stream) << str.c_str();
        }

        (*_stream) << '\n';
    }
}    // namespace csv