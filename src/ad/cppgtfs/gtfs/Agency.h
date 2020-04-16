// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_AGENCY_H_
#define AD_CPPGTFS_GTFS_AGENCY_H_

#include <string>
#include <utility>
#include "flat/Agency.h"

namespace ad::cppgtfs::gtfs
{
    class Agency
    {
    public:
        using Ref = Agency*;

        static std::string getId(Ref r) { return r->getId(); }

        Agency() = default;

        explicit Agency(std::string id, std::string name, std::string url, std::string timezone, std::string lang, std::string phone, std::string fare_url, std::string agency_email) :
            _id(std::move(id)),
            _name(std::move(name)),
            _url(std::move(url)),
            _timezone(std::move(timezone)),
            _lang(std::move(lang)),
            _phone(std::move(phone)),
            _fare_url(std::move(fare_url)),
            _agency_email(std::move(agency_email)) {}

        explicit Agency(const char* id, const char* name, const char* url, const char* timezone, const char* lang, const char* phone, const char* fare_url, const char* agency_email) :
            _id(id),
            _name(name),
            _url(url),
            _timezone(timezone),
            _lang(lang),
            _phone(phone),
            _fare_url(fare_url),
            _agency_email(agency_email) {}

        [[nodiscard]] const std::string& getId() const { return _id; }

        [[nodiscard]] const std::string& getName() const { return _name; }

        [[nodiscard]] const std::string& getUrl() const { return _url; }

        [[nodiscard]] const std::string& getTimezone() const { return _timezone; }

        [[nodiscard]] const std::string& getLang() const { return _lang; }

        [[nodiscard]] const std::string& getPhone() const { return _phone; }

        [[nodiscard]] const std::string& getFareUrl() const { return _fare_url; }

        [[nodiscard]] const std::string& getAgencyEmail() const { return _agency_email; }

        void setId(const std::string& id)
        {
            _id = id;
        }
        void setName(const std::string& name)
        {
            _name = name;
        }
        void setUrl(const std::string& url)
        {
            _url = url;
        }
        void setTimezone(const std::string& timezone)
        {
            _timezone = timezone;
        }
        void setLang(const std::string& lang)
        {
            _lang = lang;
        }
        void setPhone(const std::string& phone)
        {
            _phone = phone;
        }
        void setFareUrl(const std::string& fareUrl)
        {
            _fare_url = fareUrl;
        }
        void setAgencyEmail(const std::string& agencyEmail)
        {
            _agency_email = agencyEmail;
        }

        [[nodiscard]] flat::Agency getFlat() const
        {
            return flat::Agency{
                _id,
                _name,
                _url,
                _timezone,
                _lang,
                _phone,
                _fare_url,
                _agency_email
            };
        }

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

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_AGENCY_H_
