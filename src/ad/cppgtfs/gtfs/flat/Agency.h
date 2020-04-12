// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_AGENCY_H_
#define AD_CPPGTFS_GTFS_FLAT_AGENCY_H_

#include <string>

using std::exception;
using std::string;

namespace ad::cppgtfs::gtfs::flat
{
    struct AgencyFlds
    {
        size_t agencyNameFld;
        size_t agencyUrlFld;
        size_t agencyTimezoneFld;
        size_t agencyEmailFld;
        size_t agencyFareUrlFld;
        size_t agencyLangFld;
        size_t agencyPhoneFld;
        size_t agencyIdFld;
    };

    struct Agency
    {
        std::string id, name, url, timezone, lang, phone, fare_url, agency_email;
    };

}    // namespace ad::cppgtfs::gtfs::flat

#endif    // AD_CPPGTFS_GTFS_FLAT_AGENCY_H_
