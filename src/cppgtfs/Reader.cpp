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
    bool ReaderBase::nextShapePoint(CsvParser& csvp, ShapePoint::Flat* c, const Shape::Fields& flds) const
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
    bool ReaderBase::nextStopTime(CsvParser& csvp, StopTime::Flat* s, const StopTime::Fields& flds) const
    {
        if (csvp.readNextLine()) {
            s->at = _dataExtractor.getTime(csvp, flds.arrivalTimeFld);
            s->dt = _dataExtractor.getTime(csvp, flds.departureTimeFld);

            s->trip = _dataExtractor.getString(csvp, flds.tripIdFld);
            s->s = _dataExtractor.getString(csvp, flds.stopIdFld);
            s->sequence = _dataExtractor.getRangeInteger(csvp, flds.stopSequenceFld, 0, UINT32_MAX);
            s->headsign = _dataExtractor.getString(csvp, flds.stopHeadsignFld, "");
            s->pickupType = static_cast<StopTime::Flat::PU_DO_TYPE>(
                _dataExtractor.getRangeInteger(csvp, flds.pickUpTypeFld, 0, 3, 0));
            s->dropOffType = static_cast<StopTime::Flat::PU_DO_TYPE>(
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









    // ____________________________________________________________________________
    bool Reader::parse(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile;

        targetFeed.setPath(_path);

        parseFeedInfo(targetFeed);
        parseAgencies(targetFeed);
        parseStops(targetFeed);
        parseRoutes(targetFeed);
        parseCalendar(targetFeed);
        parseCalendarDates(targetFeed);
        parseShapes(targetFeed);
        parseTrips(targetFeed);
        parseStopTimes(targetFeed);
        parseFrequencies(targetFeed);
        parseTransfers(targetFeed);
        parseFareAttributes(targetFeed);
        parseFareRules(targetFeed);

        return true;
    }


    // ____________________________________________________________________________
    void Reader::parseTransfers(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        TransferFlat ft;
        auto flds = TransfersFields::fromCsvParser(csvp);

        while (nextTransfer(csvp, &ft, flds)) {
            Stop* fromStop = targetFeed.getStops().get(ft.fromStop);
            Stop* toStop = targetFeed.getStops().get(ft.toStop);

            if (!fromStop) {
                std::stringstream msg;
                msg << "no stop with id '" << ft.fromStop
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "from_stop_id", csvp.getCurLine());
            }

            if (!toStop) {
                std::stringstream msg;
                msg << "no stop with id '" << ft.toStop
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "to_stop_id", csvp.getCurLine());
            }
            Transfer t(fromStop, toStop, ft.type, ft.tTime);
            targetFeed.getTransfers().push_back(t);
        }
    }


    // ____________________________________________________________________________
    void Reader::parseFrequencies(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        Frequency::Flat ff;
        auto flds = Frequency::Fields::fromCsvParser(csvp);

        while (nextFrequency(csvp, &ff, flds)) {
            Frequency f(ff.startTime, ff.endTime, ff.headwaySecs, ff.exactTimes);

            auto trip = targetFeed.getTrips().get(ff.tripId);
            if (!trip) {
                std::stringstream msg;
                msg << "trip '" << ff.tripId << "' not found.";
                throw ParseException(msg.str(), "trip_id", csvp.getCurLine());
            }

            trip->addFrequency(f);
        }
    }

    // ____________________________________________________________________________
    void Reader::parseFareAttributes(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        Fare::Flat ff;
        auto flds = Fare::Fields::fromCsvParser(csvp);

        while (nextFare(csvp, &ff, flds)) {
            Agency::Ref agency = Agency::Ref();

            if (!ff.agency.empty()) {
                agency = targetFeed.getAgencies().get(ff.agency);
                if (!agency) {
                    std::stringstream msg;
                    msg << "no agency with id '" << ff.agency << "' defined, cannot "
                        << "reference here.";
                    throw ParseException(msg.str(), "agency_id", csvp.getCurLine());
                }
            }
            targetFeed.getFares().add(Fare(ff.id, ff.price, ff.currencyType, ff.paymentMethod, ff.numTransfers, agency, ff.duration));
        }
    }

    // ____________________________________________________________________________
    void Reader::parseFareRules(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        FareRule::Flat fr;
        auto flds = FareRule::Fields::fromCsvParser(csvp);

        while (nextFareRule(csvp, &fr, flds)) {
            Fare* fare = targetFeed.getFares().get(fr.fare);
            Route* route = targetFeed.getRoutes().get(fr.route);

            if (!fare) {
                std::stringstream msg;
                msg << "no fare with id '" << fr.fare << "' defined, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "fare_id", csvp.getCurLine());
            }

            if (!fr.route.empty() && !route) {
                std::stringstream msg;
                msg << "no route with id '" << fr.route << "' defined, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "route_id", csvp.getCurLine());
            }

            if (!fr.originZone.empty() && !targetFeed.getZones().count(fr.originZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.originZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "origin_id", csvp.getCurLine());
            }

            if (!fr.destZone.empty() && !targetFeed.getZones().count(fr.destZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.destZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "destination_id", csvp.getCurLine());
            }

            if (!fr.containsZone.empty() && !targetFeed.getZones().count(fr.containsZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.containsZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "contains_id", csvp.getCurLine());
            }

            FareRule r(route, fr.originZone, fr.destZone, fr.containsZone);
            fare->addFareRule(r);
        }

        targetFeed.getFares().finalize();
    }

    // ____________________________________________________________________________
    void Reader::parseFeedInfo(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        size_t feedPublisherNameFld = csvp.getFieldIndex("feed_publisher_name");
        size_t feedPublisherUrlFld = csvp.getFieldIndex("feed_publisher_url");
        size_t feedLangFld = csvp.getOptFieldIndex("feed_lang");
        size_t feedStartDateFld = csvp.getOptFieldIndex("feed_start_date");
        size_t feedEndDateFld = csvp.getOptFieldIndex("feed_end_date");
        size_t feedVersionFld = csvp.getOptFieldIndex("feed_version");

        while (csvp.readNextLine()) {
            targetFeed.setPublisherName(_dataExtractor.getString(csvp, feedPublisherNameFld));
            targetFeed.setPublisherUrl(_dataExtractor.getString(csvp, feedPublisherUrlFld));
            targetFeed.setLang(_dataExtractor.getString(csvp, feedLangFld, ""));
            targetFeed.setVersion(_dataExtractor.getString(csvp, feedVersionFld, ""));
            targetFeed.setStartDate(_dataExtractor.getServiceDate(csvp, feedStartDateFld, false));
            targetFeed.setEndDate(_dataExtractor.getServiceDate(csvp, feedEndDateFld, false));
        }
    }


    // ____________________________________________________________________________
    void Reader::parseAgencies(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);
        Agency::Ref a = (Agency::Ref());
        Agency::Flat fa;
        auto flds = Agency::Fields::fromCsvParser(csvp);

        while (nextAgency(csvp, &fa, flds)) {
            if ((Agency::Ref()) == (a = targetFeed.getAgencies().add(Agency(fa.id, fa.name, fa.url, fa.timezone, fa.lang, fa.phone, fa.fare_url, fa.agency_email)))) {
                std::stringstream msg;
                msg << "'agency_id' must be dataset unique. Collision with id '" << a->getId() << "')";
                throw ParseException(msg.str(), "agency_id", csvp.getCurLine());
            }
        }

        if ((Agency::Ref()) == a) {
            throw ParseException("the feed has no agency defined. This is a required field.", "", 1);
        }

        targetFeed.getAgencies().finalize();
    }


    // ____________________________________________________________________________
    void Reader::parseStops(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        std::map<std::string, std::pair<size_t, std::string>> parentStations;

        Stop::Flat fs;
        auto flds = Stop::Fields::fromCsvParser(csvp);

        while (nextStop(csvp, &fs, flds)) {
            targetFeed.updateBox(fs.lat, fs.lng);

            const Stop& stop =
                Stop(fs.id, fs.code, fs.name, fs.desc, fs.lat, fs.lng, fs.zone_id, fs.stop_url, fs.location_type, 0, fs.stop_timezone, fs.wheelchair_boarding, fs.platform_code);

            if (!fs.parent_station.empty()) {
                if (fs.location_type == Stop::Flat::LOCATION_TYPE::STATION) {
                    throw ParseException(
                        "a stop with location_type 'station' (1) cannot"
                        " have a parent station",
                        "parent_station",
                        csvp.getCurLine());
                }

                parentStations[stop.getId()] =
                    std::pair<size_t, std::string>(csvp.getCurLine(), fs.parent_station);
            }

            targetFeed.getZones().insert(fs.zone_id);

            if (!targetFeed.getStops().add(stop)) {
                std::stringstream msg;
                msg << "'stop_id' must be dataset unique. Collision with id '"
                    << stop.getId() << "')";
                throw ParseException(msg.str(), "stop_id", csvp.getCurLine());
            }
        }

        targetFeed.getStops().finalize();

        // second pass to resolve parentStation pointers
        for (const auto& ps : parentStations) {
            Stop* parentStation = 0;
            parentStation = targetFeed.getStops().get(ps.second.second);
            if (!parentStation) {
                std::stringstream msg;
                msg << "no stop with id '" << ps.second.second << "' defined, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "parent_station", ps.second.first);
            } else {
                targetFeed.getStops().get(ps.first)->setParentStation(parentStation);
            }
        }
    }


    // ____________________________________________________________________________
    void Reader::parseRoutes(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        Route::Flat fr;
        auto flds = Route::Fields::fromCsvParser(csvp);

        while (nextRoute(csvp, &fr, flds)) {
            Agency::Ref routeAgency = 0;

            if (!fr.agency.empty()) {
                routeAgency = targetFeed.getAgencies().get(fr.agency);
                if ((typename Agency::Ref()) == routeAgency) {
                    std::stringstream msg;
                    msg << "no agency with id '" << fr.agency << "' defined, cannot "
                        << "reference here.";
                    throw ParseException(msg.str(), "agency_id", csvp.getCurLine());
                }
            }

            if (!targetFeed.getRoutes().add(Route(fr.id, routeAgency, fr.short_name, fr.long_name, fr.desc, fr.type, fr.url, fr.color, fr.text_color))) {
                std::stringstream msg;
                msg << "'route_id' must be dataset unique. Collision with id '" << fr.id
                    << "')";
                throw ParseException(msg.str(), "route_id", csvp.getCurLine());
            }
        }

        targetFeed.getRoutes().finalize();
    }


    // ____________________________________________________________________________
    void Reader::parseCalendar(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        CalendarFlat fc;
        auto flds = CalendarFields::fromCsvParser(csvp);

        while (nextCalendar(csvp, &fc, flds)) {
            if ((typename Service::Ref()) == targetFeed.getServices().add(Service(fc.id, fc.serviceDays, fc.begin, fc.end))) {
                std::stringstream msg;
                msg << "'service_id' must be unique in calendars.txt. Collision with id '"
                    << fc.id << "')";
                throw ParseException(msg.str(), "service_id", csvp.getCurLine());
            }
        }
    }


    // ____________________________________________________________________________
    void Reader::parseCalendarDates(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        CalendarDateFlat fc;
        auto flds = CalendarDateFields::fromCsvParser(csvp);

        while (nextCalendarDate(csvp, &fc, flds)) {
            Service* e = targetFeed.getServices().get(fc.id);

            if (!e) {
                targetFeed.getServices().add(Service(fc.id));
                e = targetFeed.getServices().get(fc.id);
            }

            if (e) e->addException(fc.date, fc.type);
        }

        targetFeed.getServices().finalize();
    }

    // ____________________________________________________________________________
    void Reader::parseTrips(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        TripFlat ft;
        auto flds = TripFields::fromCsvParser(csvp);

        while (nextTrip(csvp, &ft, flds)) {
            Route* tripRoute = 0;

            tripRoute = targetFeed.getRoutes().get(ft.route);
            if (!tripRoute) {
                std::stringstream msg;
                msg << "no route with id '" << ft.route << "' defined, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "route_id", csvp.getCurLine());
            }

            typename Shape::Ref tripShape = (typename Shape::Ref());

            if (!ft.shape.empty()) {
                tripShape = targetFeed.getShapes().getRef(ft.shape);
                if (tripShape == (typename Shape::Ref())) {
                    std::stringstream msg;
                    msg << "no shape with id '" << ft.shape << "' defined, cannot "
                        << "reference here.";
                    throw ParseException(msg.str(), "shape_id", csvp.getCurLine());
                }
            }

            typename Service::Ref tripService =
                targetFeed.getServices().getRef(ft.service);

            if ((typename Service::Ref()) == tripService) {
                std::stringstream msg;
                msg << "no service with id '" << ft.service << "' defined, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "service_id", csvp.getCurLine());
            }

            if (typename Trip::Ref() == targetFeed.getTrips().add(Trip(ft.id, tripRoute, tripService, ft.headsign, ft.short_name, ft.dir, ft.block_id, tripShape, ft.wc, ft.ba))) {
                std::stringstream msg;
                msg << "'trip_id' must be dataset unique. Collision with id '"
                    << _dataExtractor.getString(csvp, flds.tripIdFld) << "')";
                throw ParseException(msg.str(), "trip_id", csvp.getCurLine());
            }
        }

        targetFeed.getTrips().finalize();
    }


    // ____________________________________________________________________________
    void Reader::parseStops(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/stops.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) {
                throw exceptions::FileNotFoundException(curFile);
            }
            parseStops(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseRoutes(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/routes.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) {
                throw exceptions::FileNotFoundException(curFile);
            }
            parseRoutes(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseCalendar(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/calendar.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseCalendar(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseCalendarDates(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/calendar_dates.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseCalendarDates(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseFeedInfo(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/feed_info.txt";

        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFeedInfo(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseAgencies(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/agency.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) {
                throw exceptions::FileNotFoundException(curFile);
            }
            parseAgencies(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseShapes(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/shapes.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseShapes(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseTrips(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/trips.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) {
                throw exceptions::FileNotFoundException(curFile);
            }
            parseTrips(targetFeed, &fs);
            fs.close();
        } catch (CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (ParseException& e) {
            // augment with file name
            e.setFileName(curFile);
            throw e;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseStopTimes(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/stop_times.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) {
                throw exceptions::FileNotFoundException(curFile);
            }
            parseStopTimes(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseFareRules(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/fare_rules.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFareRules(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseFareAttributes(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/fare_attributes.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFareAttributes(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseTransfers(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/transfers.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseTransfers(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseFrequencies(Feed& targetFeed) const
    {
        std::ifstream fs;
        std::string curFile = _path + "/frequencies.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFrequencies(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParseException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParseException& e) {
            // augment with file name
            ParseException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    void Reader::parseShapes(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        ShapePoint::Flat fp;
        auto flds = Shape::Fields::fromCsvParser(csvp);

        while (nextShapePoint(csvp, &fp, flds)) {
            auto shape = targetFeed.getShapes().get(fp.id);
            targetFeed.updateBox(fp.lat, fp.lng);

            if (!shape) {
                shape = targetFeed.getShapes().add(Shape(fp.id));
            }

            if (shape) {
                if (!shape->addPoint(ShapePoint(fp.lat, fp.lng, fp.travelDist, fp.seq))) {
                    throw ParseException(
                        "shape_pt_sequence collision, shape_pt_sequence has to be increasing for a single shape.",
                        "shape_pt_sequence",
                        csvp.getCurLine());
                }
            }
        }

        targetFeed.getShapes().finalize();
    }

    // ____________________________________________________________________________
    void Reader::parseStopTimes(Feed& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        StopTime::Flat fst;
        auto flds = StopTime::Fields::fromCsvParser(csvp);

        while (nextStopTime(csvp, &fst, flds)) {
            Stop* stop = 0;
            Trip* trip = 0;

            stop = targetFeed.getStops().get(fst.s);
            trip = targetFeed.getTrips().get(fst.trip);

            if (!stop) {
                std::stringstream msg;
                msg << "no stop with id '" << fst.s << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "stop_id", csvp.getCurLine());
            }

            if (!trip) {
                std::stringstream msg;
                msg << "no trip with id '" << fst.trip
                    << "' defined in trips.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "trip_id", csvp.getCurLine());
            }

            StopTime st(fst.at, fst.dt, stop, fst.sequence, fst.headsign, fst.pickupType, fst.dropOffType, fst.shapeDistTravelled, fst.isTimepoint);

            if (st.getArrivalTime() > st.getDepartureTime()) {
                throw ParseException("arrival time '" + st.getArrivalTime().toString() + "' is later than departure time '" + st.getDepartureTime().toString() + "'. You cannot depart earlier than you arrive.",
                                     "departure_time",
                                     csvp.getCurLine());
            }

            if (!trip->addStopTime(st)) {
                throw ParseException(
                    "stop_sequence collision, stop_sequence has "
                    "to be increasing for a single trip.",
                    "stop_sequence",
                    csvp.getCurLine());
            }
        }
    }
}    // namespace cppgtfs