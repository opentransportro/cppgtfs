// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_AGENCY_H_
#define AD_CPPGTFS_GTFS_AGENCY_H_

#include <csv/CsvParser.h>
#include <string>
#include <utility>

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;

    class Agency
    {
    public:
        struct Fields
        {
            fieldId agencyNameFld;
            fieldId agencyUrlFld;
            fieldId agencyTimezoneFld;
            fieldId agencyEmailFld;
            fieldId agencyFareUrlFld;
            fieldId agencyLangFld;
            fieldId agencyPhoneFld;
            fieldId agencyIdFld;

            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };

        struct Flat
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


        using Ref = Agency*;

        Agency() = default;

        explicit Agency(std::string id, std::string name, std::string url, std::string timezone, std::string lang, std::string phone, std::string fare_url, std::string agency_email);

        [[nodiscard]] const std::string& getId() const;

        [[nodiscard]] const std::string& getName() const;

        [[nodiscard]] const std::string& getUrl() const;

        [[nodiscard]] const std::string& getTimezone() const;

        [[nodiscard]] const std::string& getLang() const;

        [[nodiscard]] const std::string& getPhone() const;

        [[nodiscard]] const std::string& getFareUrl() const;

        [[nodiscard]] const std::string& getAgencyEmail() const;

        [[nodiscard]] Agency::Flat getFlat() const;

        void setId(const std::string& id);
        void setName(const std::string& name);
        void setUrl(const std::string& url);
        void setTimezone(const std::string& timezone);
        void setLang(const std::string& lang);
        void setPhone(const std::string& phone);
        void setFareUrl(const std::string& fareUrl);
        void setAgencyEmail(const std::string& agencyEmail);


    private:
        std::string _id;
        std::string _name;
        std::string _url;
        std::string _timezone;
        std::string _lang;
        std::string _phone;
        std::string _fare_url;
        std::string _agency_email;
    };

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_AGENCY_H_
