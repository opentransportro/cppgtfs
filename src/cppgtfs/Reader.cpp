#include <cppgtfs/Reader.h>

#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <cppgtfs/gtfs/Service.h>
#include "cppgtfs/gtfs/StopTime.h"
#include "cppgtfs/gtfs/Transfer.h"

namespace cppgtfs
{
    bool ReaderBase::nextTransfer(CsvParser& csvp, TransferFlat* t, const TransfersFields& flds) const
    {
        if (csvp.readNextLine()) {
            t->fromStop = _dataExtractor.getString(csvp, flds.fromStopIdFld);
            t->toStop = _dataExtractor.getString(csvp, flds.toStopIdFld);
            t->type = static_cast<TransferFlat::TYPE>(_dataExtractor.getRangeInteger(csvp, flds.transferTypeFld, 0, 3, 0));
            t->tTime = _dataExtractor.getRangeInteger(csvp, flds.minTransferTimeFld, 0, UINT32_MAX, -1);
            return true;
        }

        return false;
    }
    bool ReaderBase::nextFrequency(CsvParser& csvp, gtfs::Frequency::Flat* r, const gtfs::Frequency::Fields& flds) const
    {
        if (csvp.readNextLine()) {
            r->tripId = _dataExtractor.getString(csvp, flds.tripIdFld);
            r->startTime = _dataExtractor.getTime(csvp, flds.startTimeFld);
            r->endTime = _dataExtractor.getTime(csvp, flds.endTimeFld);
            r->headwaySecs = _dataExtractor.getRangeInteger(csvp, flds.headwaySecsFld, 0, UINT16_MAX);
            r->exactTimes = _dataExtractor.getRangeInteger(csvp, flds.exactTimesFld, 0, 1, 0);
            return true;
        }

        return false;
    }
    bool ReaderBase::nextFare(CsvParser& csvp, Fare::Flat* t, const Fare::Fields& flds) const
    {
        if (csvp.readNextLine()) {
            t->id = _dataExtractor.getString(csvp, flds.fareIdFld);
            t->price = _dataExtractor.getDouble(csvp, flds.priceFld);
            t->currencyType = _dataExtractor.getString(csvp, flds.currencyTypeFld);
            t->paymentMethod = static_cast<typename Fare::Flat::PAYMENT_METHOD>(_dataExtractor.getRangeInteger(csvp, flds.paymentMethodFld, 0, 1));
            t->numTransfers = static_cast<typename Fare::Flat::NUM_TRANSFERS>(_dataExtractor.getRangeInteger(csvp, flds.transfersFld, 0, 3, 3));
            t->agency = _dataExtractor.getString(csvp, flds.agencyFld, "");
            t->duration = _dataExtractor.getRangeInteger(csvp, flds.transferDurationFld, 0, INT64_MAX, -1);
        }

        return false;
    }
    bool ReaderBase::nextFareRule(CsvParser& csvp, FareRule::Flat* t, const FareRule::Fields& flds) const
    {
        if (csvp.readNextLine()) {
            t->fare = _dataExtractor.getString(csvp, flds.fareIdFld);
            t->route = _dataExtractor.getString(csvp, flds.routeIdFld, "");
            t->originZone = _dataExtractor.getString(csvp, flds.originIdFld, "");
            t->destZone = _dataExtractor.getString(csvp, flds.destinationIdFld, "");
            t->containsZone = _dataExtractor.getString(csvp, flds.containsIdFld, "");
        }

        return false;
    }
    bool ReaderBase::nextAgency(CsvParser& csvp, gtfs::Agency::Flat* a, const gtfs::Agency::Fields& flds) const
    {
        if (csvp.readNextLine()) {
            a->id = _dataExtractor.getString(csvp, flds.agencyIdFld, "");
            a->name = _dataExtractor.getString(csvp, flds.agencyNameFld);
            a->url = _dataExtractor.getString(csvp, flds.agencyUrlFld);
            a->timezone = _dataExtractor.getString(csvp, flds.agencyTimezoneFld);
            a->lang = _dataExtractor.getString(csvp, flds.agencyLangFld, "");
            a->phone = _dataExtractor.getString(csvp, flds.agencyPhoneFld, "");
            a->fare_url = _dataExtractor.getString(csvp, flds.agencyFareUrlFld, "");
            a->agency_email = _dataExtractor.getString(csvp, flds.agencyEmailFld, "");

            return true;
        }

        return false;
    }
    bool ReaderBase::nextStop(CsvParser& csvp, Stop::Flat* s, const Stop::Fields& flds) const
    {
        if (csvp.readNextLine()) {
            s->id = _dataExtractor.getString(csvp, flds.stopIdFld);
            s->code = _dataExtractor.getString(csvp, flds.stopCodeFld, "");
            s->name = _dataExtractor.getString(csvp, flds.stopNameFld);
            s->desc = _dataExtractor.getString(csvp, flds.stopDescFld, "");
            s->zone_id = _dataExtractor.getString(csvp, flds.zoneIdFld, "");
            s->stop_url = _dataExtractor.getString(csvp, flds.stopUrlFld, "");
            s->stop_timezone = _dataExtractor.getString(csvp, flds.stopTimezoneFld, "");
            s->platform_code = _dataExtractor.getString(csvp, flds.platformCodeFld, "");
            s->parent_station = _dataExtractor.getString(csvp, flds.parentStationFld, "");
            s->lat = _dataExtractor.getDouble(csvp, flds.stopLatFld);
            s->lng = _dataExtractor.getDouble(csvp, flds.stopLonFld);
            s->wheelchair_boarding = static_cast<Stop::Flat::WHEELCHAIR_BOARDING>(
                _dataExtractor.getRangeInteger(csvp, flds.wheelchairBoardingFld, 0, 2, 0));
            s->location_type = static_cast<Stop::Flat::LOCATION_TYPE>(
                _dataExtractor.getRangeInteger(csvp, flds.locationTypeFld, 0, 2, 0));

            return true;
        }

        return false;
    }
    bool ReaderBase::nextRoute(CsvParser& csvp, Route::Flat* r, const Route::Fields& flds) const
    {
        if (csvp.readNextLine()) {
            r->id = _dataExtractor.getString(csvp, flds.routeIdFld);
            r->agency = _dataExtractor.getString(csvp, flds.agencyIdFld, "");
            r->short_name = _dataExtractor.getString(csvp, flds.routeShortNameFld, "");
            r->long_name = _dataExtractor.getString(csvp, flds.routeLongNameFld, "");
            r->desc = _dataExtractor.getString(csvp, flds.routeDescFld, "");
            r->type = _dataExtractor.getRouteType(csvp, flds.routeTypeFld, _dataExtractor.getRangeInteger(csvp, flds.routeTypeFld, 0, 1702));
            r->url = _dataExtractor.getString(csvp, flds.routeUrlFld, "");
            r->color = _dataExtractor.getColorFromHexString(csvp, flds.routeColorFld, "FFFFFF");
            r->text_color = _dataExtractor.getColorFromHexString(csvp, flds.routeTextColorFld, "000000");

            return true;
        }

        return false;
    }
    bool ReaderBase::nextCalendar(CsvParser& csvp, CalendarFlat* c, const CalendarFields& flds) const
    {
        if (csvp.readNextLine()) {
            c->id = _dataExtractor.getString(csvp, flds.serviceIdFld);
            c->serviceDays = (_dataExtractor.getRangeInteger(csvp, flds.mondayFld, 0, 1)) | (_dataExtractor.getRangeInteger(csvp, flds.tuesdayFld, 0, 1) << 1) | (_dataExtractor.getRangeInteger(csvp, flds.wednesdayFld, 0, 1) << 2) | (_dataExtractor.getRangeInteger(csvp, flds.thursdayFld, 0, 1) << 3) | (_dataExtractor.getRangeInteger(csvp, flds.fridayFld, 0, 1) << 4) | (_dataExtractor.getRangeInteger(csvp, flds.saturdayFld, 0, 1) << 5) | (_dataExtractor.getRangeInteger(csvp, flds.sundayFld, 0, 1) << 6);
            c->begin = _dataExtractor.getServiceDate(csvp, flds.startDateFld, true);
            c->end = _dataExtractor.getServiceDate(csvp, flds.endDateFld, true);

            return true;
        }

        return false;
    }
    bool ReaderBase::nextCalendarDate(CsvParser& csvp, CalendarDateFlat* c, const CalendarDateFields& flds) const
    {
        if (csvp.readNextLine()) {
            c->id = _dataExtractor.getString(csvp, flds.serviceIdFld);
            c->date = _dataExtractor.getServiceDate(csvp, flds.dateFld, true);
            c->type = static_cast<CalendarDateFlat::EXCEPTION_TYPE>(
                _dataExtractor.getRangeInteger(csvp, flds.exceptionTypeFld, 1, 2));

            return true;
        }

        return false;
    }

    bool ReaderBase::nextTrip(CsvParser& csvp, TripFlat* c, const TripFields& flds) const
    {
        if (csvp.readNextLine()) {
            c->id = _dataExtractor.getString(csvp, flds.tripIdFld);
            c->route = _dataExtractor.getString(csvp, flds.routeIdFld);
            c->service = _dataExtractor.getString(csvp, flds.serviceIdFld);
            c->headsign = _dataExtractor.getString(csvp, flds.tripHeadsignFld, "");
            c->short_name = _dataExtractor.getString(csvp, flds.tripShortNameFld, "");
            c->dir = static_cast<TripFlat::DIRECTION>(_dataExtractor.getRangeInteger(csvp, flds.directionIdFld, 0, 1, 2));
            c->block_id = _dataExtractor.getString(csvp, flds.blockIdFld, "");
            c->shape = _dataExtractor.getString(csvp, flds.shapeIdFld, "");
            c->wc = static_cast<TripFlat::WC_BIKE_ACCESSIBLE>(_dataExtractor.getRangeInteger(csvp, flds.wheelchairAccessibleFld, 0, 2, 0)),
            c->ba = static_cast<TripFlat::WC_BIKE_ACCESSIBLE>(_dataExtractor.getRangeInteger(csvp, flds.bikesAllowedFld, 0, 2, 0));
            return true;
        }
        return false;
    }
    bool ReaderBase::nextShapePoint(CsvParser& csvp, ShapePointFlat* c, const ShapeFields& flds) const
    {
        if (csvp.readNextLine()) {
            c->id = _dataExtractor.getString(csvp, flds.shapeIdFld);
            c->lat = _dataExtractor.getDouble(csvp, flds.shapePtLatFld);
            c->lng = _dataExtractor.getDouble(csvp, flds.shapePtLonFld);
            c->seq = _dataExtractor.getRangeInteger(csvp, flds.shapePtSequenceFld, 0, UINT32_MAX);
            c->travelDist = -1;    // using -1 as a null value here

            if (flds.shapeDistTraveledFld < csvp.getNumColumns()) {
                if (!_dataExtractor.getString(csvp, flds.shapeDistTraveledFld, "").empty()) {
                    c->travelDist = _dataExtractor.getDouble(csvp, flds.shapeDistTraveledFld);

                    if (std::isless(c->travelDist, -0.01)) {
                        throw ParseException(
                            "negative values not supported for distances - value was: " + std::to_string(c->travelDist),
                            "shape_dist_traveled",
                            csvp.getCurLine());
                    }
                }
            }

            return true;
        }

        return false;
    }
    bool ReaderBase::nextStopTime(CsvParser& csvp, StopTimeFlat* s, const StopTimeFields& flds) const
    {
        if (csvp.readNextLine()) {
            s->at = _dataExtractor.getTime(csvp, flds.arrivalTimeFld);
            s->dt = _dataExtractor.getTime(csvp, flds.departureTimeFld);

            s->trip = _dataExtractor.getString(csvp, flds.tripIdFld);
            s->s = _dataExtractor.getString(csvp, flds.stopIdFld);
            s->sequence = _dataExtractor.getRangeInteger(csvp, flds.stopSequenceFld, 0, UINT32_MAX);
            s->headsign = _dataExtractor.getString(csvp, flds.stopHeadsignFld, "");
            s->pickupType = static_cast<StopTimeFlat::PU_DO_TYPE>(
                _dataExtractor.getRangeInteger(csvp, flds.pickUpTypeFld, 0, 3, 0));
            s->dropOffType = static_cast<StopTimeFlat::PU_DO_TYPE>(
                _dataExtractor.getRangeInteger(csvp, flds.dropOffTypeFld, 0, 3, 0));

            // if at and dt are empty, default to 0 here
            s->isTimepoint = _dataExtractor.getRangeInteger(csvp, flds.timepointFld, 0, 1, !(s->at.empty() && s->dt.empty()));

            if (s->isTimepoint && s->at.empty() && s->dt.empty()) {
                throw ParseException(
                    "if arrival_time and departure_time are empty, timepoint cannot be 1",
                    "timepoint",
                    csvp.getCurLine());
            }

            s->shapeDistTravelled = -1;    // using -1 as a null value here
            if (flds.shapeDistTraveledFld < csvp.getNumColumns()) {
                if (!_dataExtractor.getString(csvp, flds.shapeDistTraveledFld, "").empty()) {
                    s->shapeDistTravelled = _dataExtractor.getDouble(csvp, flds.shapeDistTraveledFld);

                    if (std::isless(s->shapeDistTravelled, -0.01)) {
                        throw ParseException(
                            "negative values not supported for distances (value was: " + std::to_string(s->shapeDistTravelled),
                            "shape_dist_traveled",
                            csvp.getCurLine());
                    }
                }
            }
            return true;
        }

        return false;
    }
    ReaderBase::ReaderBase(bool strict) :
        _dataExtractor(strict)
    {}

    void verifyPath(const std::string& path)
    {
        struct stat info;

        if (stat(path.c_str(), &info) != 0)
            throw exceptions::ParseException("Cannot access", path, -1);
        else if (!(info.st_mode & S_IFDIR))    // S_ISDIR() doesn't exist on my windows
            throw exceptions::ParseException("Is no directory", path, -1);
    }

    Reader::Reader(const std::string& path) :
        ReaderBase(false),
        _path(path)
    {
        verifyPath(path);
    }

    Reader::Reader(const std::string& path, bool strict) :
        ReaderBase(strict),
        _path(path)
    {
        verifyPath(path);
    }


}    // namespace cppgtfs