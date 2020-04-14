// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_AGENCY_H_
#define AD_CPPGTFS_GTFS_FLAT_AGENCY_H_

#include <string>
#include <ad/util/CsvParser.h>
using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct AgencyFlds
    {
        fieldId agencyNameFld;
        fieldId agencyUrlFld;
        fieldId agencyTimezoneFld;
        fieldId agencyEmailFld;
        fieldId agencyFareUrlFld;
        fieldId agencyLangFld;
        fieldId agencyPhoneFld;
        fieldId agencyIdFld;

        static AgencyFlds fromCsvParser(const ad::util::CsvParser& csvp);
    };

    struct Agency
    {
        std::string id;
        std::string name;
        std::string url;
        std::string timezone;
        std::string lang;
        std::string phone;
        std::string fare_url;
        std::string agency_email;
    };

}    // namespace ad::cppgtfs::gtfs::flat

#endif    // AD_CPPGTFS_GTFS_FLAT_AGENCY_H_
