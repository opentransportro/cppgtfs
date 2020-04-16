#include <ad/cppgtfs/gtfs/flat/Agency.h>

namespace ad::cppgtfs::gtfs::flat
{
    AgencyFlds AgencyFlds::fromCsvParser(const ad::util::CsvParser& csvp)
    {
        flat::AgencyFlds r;
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
