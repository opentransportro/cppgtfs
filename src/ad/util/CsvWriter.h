// Copyright 2018, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_UTIL_CSVWRITER_H_
#define AD_UTIL_CSVWRITER_H_

#include <stdint.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * A writer for CSV files, as defined at
 * http://tools.ietf.org/html/rfc4180#page-2
 *
 * This parser is an extension of the original AD CSV parser. It can handle
 * quoted strings and quote escapes as well as BOMs.
 */
namespace ad {
namespace util {

typedef std::vector<std::string> HeaderList;
typedef std::vector<std::string> Line;

class CsvWriter {
 public:
  // Initializes the parser by opening the file
  CsvWriter(std::ostream* str, const HeaderList& headers);

  bool writeDouble(double d);
  bool writeString(const std::string& str);
  bool writeInt(int i);
  void skip();

  void flushLine();

 private:
  std::ostream* _stream;
  HeaderList _headers;
  Line _curL;
  bool _hWritten;
  char _delim;

  bool writeRawString(const std::string& str);
  void writeStrArr(const std::vector<std::string>& arr);

  std::string escStr(const std::string& str) const;

};
}  // namespace util
}  // namespace ad

#endif  // AD_UTIL_CSVWRITER_H_
