#include <cppgtfs/gtfs/Agency.h>

namespace cppgtfs::gtfs
{
    Agency::Agency(std::string id, std::string name, std::string url, std::string timezone, std::string lang, std::string phone, std::string fare_url, std::string agency_email) :
        _id(std::move(id)),
        _name(std::move(name)),
        _url(std::move(url)),
        _timezone(std::move(timezone)),
        _lang(std::move(lang)),
        _phone(std::move(phone)),
        _fare_url(std::move(fare_url)),
        _agency_email(std::move(agency_email)) {}

    const std::string& Agency::getId() const { return _id; }
    const std::string& Agency::getName() const { return _name; }
    const std::string& Agency::getUrl() const { return _url; }
    const std::string& Agency::getTimezone() const { return _timezone; }
    const std::string& Agency::getLang() const { return _lang; }
    const std::string& Agency::getPhone() const { return _phone; }
    const std::string& Agency::getFareUrl() const { return _fare_url; }
    const std::string& Agency::getAgencyEmail() const { return _agency_email; }

    void Agency::setId(const std::string& id)
    {
        _id = id;
    }
    void Agency::setName(const std::string& name)
    {
        _name = name;
    }
    void Agency::setUrl(const std::string& url)
    {
        _url = url;
    }
    void Agency::setTimezone(const std::string& timezone)
    {
        _timezone = timezone;
    }
    void Agency::setLang(const std::string& lang)
    {
        _lang = lang;
    }
    void Agency::setPhone(const std::string& phone)
    {
        _phone = phone;
    }
    void Agency::setFareUrl(const std::string& fareUrl)
    {
        _fare_url = fareUrl;
    }
    void Agency::setAgencyEmail(const std::string& agencyEmail)
    {
        _agency_email = agencyEmail;
    }

    AgencyFlat Agency::getFlat() const
    {
        return AgencyFlat{
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
    AgencyFields AgencyFields::fromCsvParser(const csv::CsvParser& csvp)
    {
        AgencyFields r;
        r.agencyNameFld = csvp.getFieldIndex("agency_name");
        r.agencyUrlFld = csvp.getFieldIndex("agency_url");
        r.agencyTimezoneFld = csvp.getFieldIndex("agency_timezone");
        r.agencyEmailFld = csvp.getOptFieldIndex("agency_email");
        r.agencyFareUrlFld = csvp.getOptFieldIndex("agency_fare_url");
        r.agencyLangFld = csvp.getOptFieldIndex("agency_lang");
        r.agencyPhoneFld = csvp.getOptFieldIndex("agency_phone");
        r.agencyIdFld = csvp.getOptFieldIndex("agency_id");
        return r;
    }
}