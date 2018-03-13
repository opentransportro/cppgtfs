// Copyright 2018, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_WRITER_H_
#define AD_CPPGTFS_WRITER_H_

#include <stdint.h>
#include <boost/filesystem.hpp>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "ad/util/CsvWriter.h"
#include "gtfs/Feed.h"

using std::string;
using ad::util::CsvWriter;

// A GTFS writer

namespace ad {
namespace cppgtfs {

class Writer {
 public:
  // Default initialization.
  Writer() {}

  // write a GtfsFeed to a zip/folder
  bool write(gtfs::Feed* sourceFeed, std::string path) const;

 private:
  bool writeAgencies(gtfs::Feed* f, std::ostream* os) const;
  bool writeStops(gtfs::Feed* f, std::ostream* os) const;
  bool writeShapes(gtfs::Feed* f, std::ostream* os) const;
  bool writeTrips(gtfs::Feed* f, std::ostream* os) const;
  bool writeStopTimes(gtfs::Feed* f, std::ostream* os) const;
  bool writeRoutes(gtfs::Feed* f, std::ostream* os) const;
  bool writeFeedInfo(gtfs::Feed* f, std::ostream* os) const;
  bool writeTransfers(gtfs::Feed* f, std::ostream* os) const;
  bool writeCalendar(gtfs::Feed* f, std::ostream* os) const;
  bool writeCalendarDates(gtfs::Feed* f, std::ostream* os) const;
  bool writeFrequencies(gtfs::Feed* f, std::ostream* os) const;
};
}  // namespace cppgtfs
}  // namespace ad

#endif  // AD_CPPGTFS_WRITER_H_