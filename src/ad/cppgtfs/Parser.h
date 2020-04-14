// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_PARSER_H_
#define AD_CPPGTFS_PARSER_H_

#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "ad/util/CsvParser.h"
#include "ad/cppgtfs/gtfs/Feed.h"
#include "ad/cppgtfs/gtfs/flat/Agency.h"
#include "ad/cppgtfs/gtfs/flat/Frequency.h"
#include "ad/cppgtfs/gtfs/flat/Route.h"
#include "ad/cppgtfs/gtfs/flat/Service.h"
#include "ad/cppgtfs/gtfs/flat/Shape.h"
#include "ad/cppgtfs/gtfs/flat/Transfer.h"


using namespace ad::cppgtfs::gtfs;
using namespace ad::util;

// A GTFS parser
namespace ad::cppgtfs
{
    class ParserException : public std::exception
    {
    public:
        ParserException(std::string msg, std::string field_name, int64_t line, std::string file_name) :
            _msg(msg),
            _field_name(field_name),
            _line(line),
            _file_name(file_name) {}

        ParserException(std::string msg, std::string field_name, int64_t line) :
            _msg(msg), _field_name(field_name), _line(line), _file_name("?") {}

        ~ParserException() throw() {}

        virtual const char* what() const throw()
        {
            std::stringstream ss;
            ss << _file_name << ":";
            if (_line > -1) ss << _line << ":";
            if (!_field_name.empty()) ss << " in field '" << _field_name << "',";
            ss << " " << _msg;
            _what_msg = ss.str();
            return _what_msg.c_str();
        }

        virtual uint64_t getLine() const throw() { return _line; }

        void setFileName(const std::string& fn) { _file_name = fn; }

    private:
        mutable std::string _what_msg;
        std::string _msg;
        std::string _field_name;
        int64_t _line;
        std::string _file_name;
    };

    class Parser
    {
    public:
        // Default initialization.
        Parser() :
            _strict(false) {}

        explicit Parser(bool strict) :
            _strict(strict) {}

        // parse a zip/folder into a GtfsFeed
        FEEDTPL
        bool parse(FEEDB* targetFeed, const std::string& path) const;

        inline std::string getString(const CsvParser& csv, size_t field) const;

        inline std::string getString(const CsvParser& csv, size_t field, const std::string& def) const;

        inline double getDouble(const CsvParser& csv, size_t field) const;

        inline double getDouble(const CsvParser& csv, size_t fld, double def) const;

        inline int64_t getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv) const;

        inline int64_t getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv, int64_t def) const;

        inline uint32_t getColorFromHexString(const CsvParser& csv, size_t field, const std::string& def) const;

        inline ServiceDate getServiceDate(const CsvParser& csv, size_t field) const;

        inline ServiceDate getServiceDate(const CsvParser& csv, size_t field, bool req) const;

        inline Time getTime(const CsvParser& csv, size_t field) const;

        inline flat::Route::TYPE getRouteType(const CsvParser& csv, size_t field, int64_t t) const;

        inline void fileNotFound(const std::string& file) const;

        inline bool nextAgency(CsvParser* csvp, flat::Agency* a, const flat::AgencyFlds&) const;

        inline bool nextStop(CsvParser* csvp, flat::Stop* s, const flat::StopFlds&) const;

        inline bool nextRoute(CsvParser* csvp, flat::Route* s, const flat::RouteFlds&) const;

        inline bool nextCalendar(CsvParser* csvp, flat::Calendar* s, const flat::CalendarFlds&) const;

        inline bool nextCalendarDate(CsvParser* csvp, flat::CalendarDate* s, const flat::CalendarDateFlds&) const;

        inline bool nextFrequency(CsvParser* csvp, flat::Frequency* s, const flat::FrequencyFlds&) const;

        inline bool nextTransfer(CsvParser* csvp, flat::Transfer* s, const flat::TransfersFlds&) const;

        inline bool nextFare(CsvParser* csvp, flat::Fare* s, const flat::FareFlds&) const;

        inline bool nextFareRule(CsvParser* csvp, flat::FareRule* s, const flat::FareRuleFlds&) const;

        inline bool nextShapePoint(CsvParser* csvp, flat::ShapePoint* s, const flat::ShapeFlds&) const;

        inline bool nextTrip(CsvParser* csvp, flat::Trip* s, const flat::TripFlds&) const;

        inline bool nextStopTime(CsvParser* csvp, flat::StopTime* s, const flat::StopTimeFlds&) const;

        FEEDTPL
        void parseAgencies(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseStops(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseRoutes(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseTrips(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseStopTimes(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseCalendar(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseCalendarDates(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseFareAttributes(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseFareRules(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseShapes(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseFrequencies(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseTransfers(FEEDB* targetFeed, const std::string& path) const;

        FEEDTPL
        void parseFeedInfo(FEEDB* targetFeed, const std::string& path) const;

    private:
        bool _strict;

        FEEDTPL
        void parseAgencies(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseStops(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseRoutes(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseTrips(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseStopTimes(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseCalendar(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseCalendarDates(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseFareAttributes(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseFareRules(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseShapes(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseFrequencies(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseTransfers(FEEDB* targetFeed, std::istream*) const;

        FEEDTPL
        void parseFeedInfo(FEEDB* targetFeed, std::istream*) const;
    };


    // ____________________________________________________________________________
    FEEDTPL
    bool Parser::parse(FEEDB* targetFeed, const std::string& path) const
    {
        std::ifstream fs;
        std::string gtfsPath(path);
        std::string curFile;

        targetFeed->setPath(gtfsPath);

        parseFeedInfo(targetFeed, path);
        parseAgencies(targetFeed, path);
        parseStops(targetFeed, path);
        parseRoutes(targetFeed, path);
        parseCalendar(targetFeed, path);
        parseCalendarDates(targetFeed, path);
        parseShapes(targetFeed, path);
        parseTrips(targetFeed, path);
        parseStopTimes(targetFeed, path);
        parseFrequencies(targetFeed, path);
        parseTransfers(targetFeed, path);
        parseFareAttributes(targetFeed, path);
        parseFareRules(targetFeed, path);

        return true;
    }


    // ____________________________________________________________________________
    inline bool Parser::nextTransfer(CsvParser* csvp, flat::Transfer* t, const flat::TransfersFlds& flds) const
    {
        if (csvp->readNextLine()) {
            t->fromStop = getString(*csvp, flds.fromStopIdFld);
            t->toStop = getString(*csvp, flds.toStopIdFld);
            t->type = static_cast<flat::Transfer::TYPE>(
                getRangeInteger(*csvp, flds.transferTypeFld, 0, 3, 0));
            t->tTime =
                getRangeInteger(*csvp, flds.minTransferTimeFld, 0, UINT32_MAX, -1);
            return true;
        }

        return false;
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseTransfers(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Transfer ft;
        auto flds = flat::TransfersFlds::fromCsvParser(csvp);

        while (nextTransfer(&csvp, &ft, flds)) {
            StopT* fromStop = targetFeed->getStops().get(ft.fromStop);
            StopT* toStop = targetFeed->getStops().get(ft.toStop);

            if (!fromStop) {
                std::stringstream msg;
                msg << "no stop with id '" << ft.fromStop
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "from_stop_id", csvp.getCurLine());
            }

            if (!toStop) {
                std::stringstream msg;
                msg << "no stop with id '" << ft.toStop
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "to_stop_id", csvp.getCurLine());
            }
            Transfer t(fromStop, toStop, ft.type, ft.tTime);
            targetFeed->getTransfers().push_back(t);
        }
    }



// ____________________________________________________________________________
    inline bool Parser::nextFrequency(CsvParser* csvp, flat::Frequency* r, const flat::FrequencyFlds& flds) const
    {
        if (csvp->readNextLine()) {
            r->tripId = getString(*csvp, flds.tripIdFld);
            r->startTime = getTime(*csvp, flds.startTimeFld);
            r->endTime = getTime(*csvp, flds.endTimeFld);
            r->headwaySecs = getRangeInteger(*csvp, flds.headwaySecsFld, 0, UINT16_MAX);
            r->exactTimes = getRangeInteger(*csvp, flds.exactTimesFld, 0, 1, 0);
            return true;
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFrequencies(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Frequency ff;
        auto flds = flat::FrequencyFlds::fromCsvParser(csvp);

        while (nextFrequency(&csvp, &ff, flds)) {
            Frequency f(ff.startTime, ff.endTime, ff.headwaySecs, ff.exactTimes);

            auto trip = targetFeed->getTrips().get(ff.tripId);
            if (!trip) {
                std::stringstream msg;
                msg << "trip '" << ff.tripId << "' not found.";
                throw ParserException(msg.str(), "trip_id", csvp.getCurLine());
            }

            trip->addFrequency(f);
        }
    }

// ____________________________________________________________________________
    inline bool Parser::nextFare(CsvParser* csvp, flat::Fare* t, const flat::FareFlds& flds) const
    {
        if (csvp->readNextLine()) {
            t->id = getString(*csvp, flds.fareIdFld);
            t->price = getDouble(*csvp, flds.priceFld);
            t->currencyType = getString(*csvp, flds.currencyTypeFld);
            t->paymentMethod = static_cast<typename flat::Fare::PAYMENT_METHOD>(
                getRangeInteger(*csvp, flds.paymentMethodFld, 0, 1));
            t->numTransfers = static_cast<typename flat::Fare::NUM_TRANSFERS>(
                getRangeInteger(*csvp, flds.transfersFld, 0, 3, 3));
            t->agency = getString(*csvp, flds.agencyFld, "");
            t->duration =
                getRangeInteger(*csvp, flds.transferDurationFld, 0, INT64_MAX, -1);
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFareAttributes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Fare ff;
        auto flds = flat::FareFlds::fromCsvParser(csvp);

        while (nextFare(&csvp, &ff, flds)) {
            typename AgencyT::Ref agency = typename AgencyT::Ref();

            if (!ff.agency.empty()) {
                agency = targetFeed->getAgencies().get(ff.agency);
                if (!agency) {
                    std::stringstream msg;
                    msg << "no agency with id '" << ff.agency << "' defined, cannot "
                        << "reference here.";
                    throw ParserException(msg.str(), "agency_id", csvp.getCurLine());
                }
            }

            targetFeed->getFares().add(FareT<RouteT>(ff.id, ff.price, ff.currencyType, ff.paymentMethod, ff.numTransfers, agency, ff.duration));
        }
    }

// ____________________________________________________________________________
    inline bool Parser::nextFareRule(CsvParser* csvp, flat::FareRule* t, const flat::FareRuleFlds& flds) const
    {
        if (csvp->readNextLine()) {
            t->fare = getString(*csvp, flds.fareIdFld);
            t->route = getString(*csvp, flds.routeIdFld, "");
            t->originZone = getString(*csvp, flds.originIdFld, "");
            t->destZone = getString(*csvp, flds.destinationIdFld, "");
            t->containsZone = getString(*csvp, flds.containsIdFld, "");
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFareRules(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::FareRule fr;
        auto flds = flat::FareRuleFlds::fromCsvParser(csvp);

        while (nextFareRule(&csvp, &fr, flds)) {
            Fare<RouteT>* fare = targetFeed->getFares().get(fr.fare);
            RouteT* route = targetFeed->getRoutes().get(fr.route);

            if (!fare) {
                std::stringstream msg;
                msg << "no fare with id '" << fr.fare << "' defined, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "fare_id", csvp.getCurLine());
            }

            if (!fr.route.empty() && !route) {
                std::stringstream msg;
                msg << "no route with id '" << fr.route << "' defined, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "route_id", csvp.getCurLine());
            }

            if (!fr.originZone.empty() && !targetFeed->getZones().count(fr.originZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.originZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "origin_id", csvp.getCurLine());
            }

            if (!fr.destZone.empty() && !targetFeed->getZones().count(fr.destZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.destZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "destination_id", csvp.getCurLine());
            }

            if (!fr.containsZone.empty() && !targetFeed->getZones().count(fr.containsZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.containsZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "contains_id", csvp.getCurLine());
            }

            FareRule<RouteT> r(route, fr.originZone, fr.destZone, fr.containsZone);
            fare->addFareRule(r);
        }

        targetFeed->getFares().finalize();
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFeedInfo(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        size_t feedPublisherNameFld = csvp.getFieldIndex("feed_publisher_name");
        size_t feedPublisherUrlFld = csvp.getFieldIndex("feed_publisher_url");
        size_t feedLangFld = csvp.getOptFieldIndex("feed_lang");
        size_t feedStartDateFld = csvp.getOptFieldIndex("feed_start_date");
        size_t feedEndDateFld = csvp.getOptFieldIndex("feed_end_date");
        size_t feedVersionFld = csvp.getOptFieldIndex("feed_version");

        while (csvp.readNextLine()) {
            targetFeed->setPublisherName(getString(csvp, feedPublisherNameFld));
            targetFeed->setPublisherUrl(getString(csvp, feedPublisherUrlFld));
            targetFeed->setLang(getString(csvp, feedLangFld, ""));
            targetFeed->setVersion(getString(csvp, feedVersionFld, ""));
            targetFeed->setStartDate(getServiceDate(csvp, feedStartDateFld, false));
            targetFeed->setEndDate(getServiceDate(csvp, feedEndDateFld, false));
        }
    }

// ____________________________________________________________________________
    inline bool Parser::nextAgency(CsvParser* csvp, flat::Agency* a, const flat::AgencyFlds& flds) const
    {
        if (csvp->readNextLine()) {
            a->id = getString(*csvp, flds.agencyIdFld, "");
            a->name = getString(*csvp, flds.agencyNameFld);
            a->url = getString(*csvp, flds.agencyUrlFld);
            a->timezone = getString(*csvp, flds.agencyTimezoneFld);
            a->lang = getString(*csvp, flds.agencyLangFld, "");
            a->phone = getString(*csvp, flds.agencyPhoneFld, "");
            a->fare_url = getString(*csvp, flds.agencyFareUrlFld, "");
            a->agency_email = getString(*csvp, flds.agencyEmailFld, "");

            return true;
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseAgencies(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);
        typename AgencyT::Ref a = (typename AgencyT::Ref());
        flat::Agency fa;
        auto flds = flat::AgencyFlds::fromCsvParser(csvp);

        while (nextAgency(&csvp, &fa, flds)) {
            if ((typename AgencyT::Ref()) == (a = targetFeed->getAgencies().add(Agency(fa.id, fa.name, fa.url, fa.timezone, fa.lang, fa.phone, fa.fare_url, fa.agency_email)))) {
                std::stringstream msg;
                msg << "'agency_id' must be dataset unique. Collision with id '"
                    << a->getId() << "')";
                throw ParserException(msg.str(), "agency_id", csvp.getCurLine());
            }
        }

        if ((typename AgencyT::Ref()) == a) {
            throw ParserException(
                "the feed has no agency defined."
                " This is a required field.",
                "",
                1);
        }

        targetFeed->getAgencies().finalize();
    }

// ____________________________________________________________________________
    inline bool Parser::nextStop(CsvParser* csvp, flat::Stop* s, const flat::StopFlds& flds) const
    {
        if (csvp->readNextLine()) {
            s->id = getString(*csvp, flds.stopIdFld);
            s->code = getString(*csvp, flds.stopCodeFld, "");
            s->name = getString(*csvp, flds.stopNameFld);
            s->desc = getString(*csvp, flds.stopDescFld, "");
            s->zone_id = getString(*csvp, flds.zoneIdFld, "");
            s->stop_url = getString(*csvp, flds.stopUrlFld, "");
            s->stop_timezone = getString(*csvp, flds.stopTimezoneFld, "");
            s->platform_code = getString(*csvp, flds.platformCodeFld, "");
            s->parent_station = getString(*csvp, flds.parentStationFld, "");
            s->lat = getDouble(*csvp, flds.stopLatFld);
            s->lng = getDouble(*csvp, flds.stopLonFld);
            s->wheelchair_boarding = static_cast<flat::Stop::WHEELCHAIR_BOARDING>(
                getRangeInteger(*csvp, flds.wheelchairBoardingFld, 0, 2, 0));
            s->location_type = static_cast<flat::Stop::LOCATION_TYPE>(
                getRangeInteger(*csvp, flds.locationTypeFld, 0, 2, 0));

            return true;
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseStops(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        std::map<std::string, std::pair<size_t, std::string>> parentStations;

        flat::Stop fs;
        auto flds = flat::StopFlds::fromCsvParser(csvp);

        while (nextStop(&csvp, &fs, flds)) {
            targetFeed->updateBox(fs.lat, fs.lng);

            const StopT& stop =
                StopT(fs.id, fs.code, fs.name, fs.desc, fs.lat, fs.lng, fs.zone_id, fs.stop_url, fs.location_type, 0, fs.stop_timezone, fs.wheelchair_boarding, fs.platform_code);

            if (!fs.parent_station.empty()) {
                if (fs.location_type == flat::Stop::LOCATION_TYPE::STATION) {
                    throw ParserException(
                        "a stop with location_type 'station' (1) cannot"
                        " have a parent station",
                        "parent_station",
                        csvp.getCurLine());
                }

                parentStations[stop.getId()] =
                    std::pair<size_t, std::string>(csvp.getCurLine(), fs.parent_station);
            }

            targetFeed->getZones().insert(fs.zone_id);

            if (!targetFeed->getStops().add(stop)) {
                std::stringstream msg;
                msg << "'stop_id' must be dataset unique. Collision with id '"
                    << stop.getId() << "')";
                throw ParserException(msg.str(), "stop_id", csvp.getCurLine());
            }
        }

        targetFeed->getStops().finalize();

        // second pass to resolve parentStation pointers
        for (const auto& ps : parentStations) {
            StopT* parentStation = 0;
            parentStation = targetFeed->getStops().get(ps.second.second);
            if (!parentStation) {
                std::stringstream msg;
                msg << "no stop with id '" << ps.second.second << "' defined, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "parent_station", ps.second.first);
            } else {
                targetFeed->getStops().get(ps.first)->setParentStation(parentStation);
            }
        }
    }


// ____________________________________________________________________________
    inline bool Parser::nextRoute(CsvParser* csvp, flat::Route* r, const flat::RouteFlds& flds) const
    {
        if (csvp->readNextLine()) {
            r->id = getString(*csvp, flds.routeIdFld);
            r->agency = getString(*csvp, flds.agencyIdFld, "");
            r->short_name = getString(*csvp, flds.routeShortNameFld, "");
            r->long_name = getString(*csvp, flds.routeLongNameFld, "");
            r->desc = getString(*csvp, flds.routeDescFld, "");
            r->type = getRouteType(*csvp, flds.routeTypeFld, getRangeInteger(*csvp, flds.routeTypeFld, 0, 1702));
            r->url = getString(*csvp, flds.routeUrlFld, "");
            r->color = getColorFromHexString(*csvp, flds.routeColorFld, "FFFFFF");
            r->text_color = getColorFromHexString(*csvp, flds.routeTextColorFld, "000000");

            return true;
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseRoutes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Route fr;
        auto flds = flat::RouteFlds::fromCsvParser(csvp);

        while (nextRoute(&csvp, &fr, flds)) {
            typename AgencyT::Ref routeAgency = 0;

            if (!fr.agency.empty()) {
                routeAgency = targetFeed->getAgencies().get(fr.agency);
                if ((typename AgencyT::Ref()) == routeAgency) {
                    std::stringstream msg;
                    msg << "no agency with id '" << fr.agency << "' defined, cannot "
                        << "reference here.";
                    throw ParserException(msg.str(), "agency_id", csvp.getCurLine());
                }
            }

            if (!targetFeed->getRoutes().add(RouteT(fr.id, routeAgency, fr.short_name, fr.long_name, fr.desc, fr.type, fr.url, fr.color, fr.text_color))) {
                std::stringstream msg;
                msg << "'route_id' must be dataset unique. Collision with id '" << fr.id
                    << "')";
                throw ParserException(msg.str(), "route_id", csvp.getCurLine());
            }
        }

        targetFeed->getRoutes().finalize();
    }


// ____________________________________________________________________________
    inline bool Parser::nextCalendar(CsvParser* csvp, flat::Calendar* c, const flat::CalendarFlds& flds) const
    {
        if (csvp->readNextLine()) {
            c->id = getString(*csvp, flds.serviceIdFld);
            c->serviceDays = (getRangeInteger(*csvp, flds.mondayFld, 0, 1)) | (getRangeInteger(*csvp, flds.tuesdayFld, 0, 1) << 1) | (getRangeInteger(*csvp, flds.wednesdayFld, 0, 1) << 2) | (getRangeInteger(*csvp, flds.thursdayFld, 0, 1) << 3) | (getRangeInteger(*csvp, flds.fridayFld, 0, 1) << 4) | (getRangeInteger(*csvp, flds.saturdayFld, 0, 1) << 5) | (getRangeInteger(*csvp, flds.sundayFld, 0, 1) << 6);
            c->begin = getServiceDate(*csvp, flds.startDateFld, true);
            c->end = getServiceDate(*csvp, flds.endDateFld, true);

            return true;
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseCalendar(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Calendar fc;
        auto flds = flat::CalendarFlds::fromCsvParser(csvp);

        while (nextCalendar(&csvp, &fc, flds)) {
            if ((typename ServiceT::Ref()) == targetFeed->getServices().add(ServiceT(fc.id, fc.serviceDays, fc.begin, fc.end))) {
                std::stringstream msg;
                msg << "'service_id' must be unique in calendars.txt. Collision with id '"
                    << fc.id << "')";
                throw ParserException(msg.str(), "service_id", csvp.getCurLine());
            }
        }
    }


// ____________________________________________________________________________
    inline bool Parser::nextCalendarDate(
        CsvParser* csvp,
        flat::CalendarDate* c,
        const flat::CalendarDateFlds& flds) const
    {
        if (csvp->readNextLine()) {
            c->id = getString(*csvp, flds.serviceIdFld);
            c->date = getServiceDate(*csvp, flds.dateFld, true);
            c->type = static_cast<flat::CalendarDate::EXCEPTION_TYPE>(
                getRangeInteger(*csvp, flds.exceptionTypeFld, 1, 2));

            return true;
        }

        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseCalendarDates(FEEDB* targetFeed,
                                    std::istream* s) const
    {
        CsvParser csvp(s);

        flat::CalendarDate fc;
        auto flds = flat::CalendarDateFlds::fromCsvParser(csvp);

        while (nextCalendarDate(&csvp, &fc, flds)) {
            ServiceT* e = targetFeed->getServices().get(fc.id);

            if (!e) {
                targetFeed->getServices().add(ServiceT(fc.id));
                e = targetFeed->getServices().get(fc.id);
            }

            if (e) e->addException(fc.date, fc.type);
        }

        targetFeed->getServices().finalize();
    }


// ____________________________________________________________________________
    inline bool Parser::nextTrip(CsvParser* csvp, flat::Trip* c, const flat::TripFlds& flds) const
    {
        if (csvp->readNextLine()) {
            c->id = getString(*csvp, flds.tripIdFld);
            c->route = getString(*csvp, flds.routeIdFld);
            c->service = getString(*csvp, flds.serviceIdFld);
            c->headsign = getString(*csvp, flds.tripHeadsignFld, "");
            c->short_name = getString(*csvp, flds.tripShortNameFld, "");
            c->dir = static_cast<flat::Trip::DIRECTION>(
                getRangeInteger(*csvp, flds.directionIdFld, 0, 1, 2));
            c->block_id = getString(*csvp, flds.blockIdFld, "");
            c->shape = getString(*csvp, flds.shapeIdFld, "");
            c->wc = static_cast<flat::Trip::WC_BIKE_ACCESSIBLE>(
                getRangeInteger(*csvp, flds.wheelchairAccessibleFld, 0, 2, 0)),
                c->ba = static_cast<flat::Trip::WC_BIKE_ACCESSIBLE>(
                    getRangeInteger(*csvp, flds.bikesAllowedFld, 0, 2, 0));
            return true;
        }
        return false;
    }

// ____________________________________________________________________________
    FEEDTPL
    void Parser::parseTrips(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Trip ft;
        auto flds = flat::TripFlds::fromCsvParser(csvp);

        while (nextTrip(&csvp, &ft, flds)) {
            RouteT* tripRoute = 0;

            tripRoute = targetFeed->getRoutes().get(ft.route);
            if (!tripRoute) {
                std::stringstream msg;
                msg << "no route with id '" << ft.route << "' defined, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "route_id", csvp.getCurLine());
            }

            typename ShapeT::Ref tripShape = (typename ShapeT::Ref());

            if (!ft.shape.empty()) {
                tripShape = targetFeed->getShapes().getRef(ft.shape);
                if (tripShape == (typename ShapeT::Ref())) {
                    std::stringstream msg;
                    msg << "no shape with id '" << ft.shape << "' defined, cannot "
                        << "reference here.";
                    throw ParserException(msg.str(), "shape_id", csvp.getCurLine());
                }
            }

            typename ServiceT::Ref tripService =
                targetFeed->getServices().getRef(ft.service);

            if ((typename ServiceT::Ref()) == tripService) {
                std::stringstream msg;
                msg << "no service with id '" << ft.service << "' defined, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "service_id", csvp.getCurLine());
            }

            if (typename TripB<StopTimeT<StopT>, ServiceT, RouteT, ShapeT>::Ref() == targetFeed->getTrips().add(TripB<StopTimeT<StopT>, ServiceT, RouteT, ShapeT>(ft.id, tripRoute, tripService, ft.headsign, ft.short_name, ft.dir, ft.block_id, tripShape, ft.wc, ft.ba))) {
                std::stringstream msg;
                msg << "'trip_id' must be dataset unique. Collision with id '"
                    << getString(csvp, flds.tripIdFld) << "')";
                throw ParserException(msg.str(), "trip_id", csvp.getCurLine());
            }
        }

        targetFeed->getTrips().finalize();
    }

// ____________________________________________________________________________
    inline bool Parser::nextShapePoint(CsvParser* csvp, flat::ShapePoint* c, const flat::ShapeFlds& flds) const
    {
        if (csvp->readNextLine()) {
            c->id = getString(*csvp, flds.shapeIdFld);
            c->lat = getDouble(*csvp, flds.shapePtLatFld);
            c->lng = getDouble(*csvp, flds.shapePtLonFld);
            c->seq = getRangeInteger(*csvp, flds.shapePtSequenceFld, 0, UINT32_MAX);
            c->travelDist = -1;    // using -1 as a null value here

            if (flds.shapeDistTraveledFld < csvp->getNumColumns()) {
                if (!getString(*csvp, flds.shapeDistTraveledFld, "").empty()) {
                    c->travelDist = getDouble(*csvp, flds.shapeDistTraveledFld);

                    if (std::isless(c->travelDist, -0.01)) {
                        throw ParserException(
                            "negative values not supported for distances - value was: " + std::to_string(c->travelDist),
                            "shape_dist_traveled",
                            csvp->getCurLine());
                    }
                }
            }

            return true;
        }

        return false;
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseStops(FEEDB* targetFeed,
                            const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/stops.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) fileNotFound(curFile);
            parseStops(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseRoutes(FEEDB* targetFeed,
                             const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/routes.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) fileNotFound(curFile);
            parseRoutes(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseCalendar(FEEDB* targetFeed,
                               const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/calendar.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseCalendar(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseCalendarDates(FEEDB* targetFeed,
                                    const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/calendar_dates.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseCalendarDates(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFeedInfo(FEEDB* targetFeed,
                               const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/feed_info.txt";

        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFeedInfo(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseAgencies(FEEDB* targetFeed,
                               const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/agency.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) fileNotFound(curFile);
            parseAgencies(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseShapes(FEEDB* targetFeed,
                             const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/shapes.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseShapes(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseTrips(FEEDB* targetFeed, const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/trips.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) fileNotFound(curFile);
            parseTrips(targetFeed, &fs);
            fs.close();
        } catch (CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (ParserException& e) {
            // augment with file name
            e.setFileName(curFile);
            throw e;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseStopTimes(FEEDB* targetFeed, const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/stop_times.txt";
        try {
            fs.open(curFile.c_str());
            if (!fs.good()) fileNotFound(curFile);
            parseStopTimes(targetFeed, &fs);
            fs.close();
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFareRules(FEEDB* targetFeed, const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/fare_rules.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFareRules(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFareAttributes(FEEDB* targetFeed,
                                     const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/fare_attributes.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFareAttributes(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseTransfers(FEEDB* targetFeed,
                                const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/transfers.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseTransfers(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseFrequencies(FEEDB* targetFeed,
                                  const std::string& path) const
    {
        std::ifstream fs;
        std::string curFile = path + "/frequencies.txt";
        try {
            fs.open(curFile.c_str());
            if (fs.good()) {
                parseFrequencies(targetFeed, &fs);
                fs.close();
            }
        } catch (const CsvParserException& e) {
            throw ParserException(e.getMsg(), e.getFieldName(), e.getLine(), curFile.c_str());
        } catch (const ParserException& e) {
            // augment with file name
            ParserException fe = e;
            fe.setFileName(curFile.c_str());
            throw fe;
        }
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseShapes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::ShapePoint fp;
        auto flds = flat::ShapeFlds::fromCsvParser(csvp);

        while (nextShapePoint(&csvp, &fp, flds)) {
            auto shape = targetFeed->getShapes().get(fp.id);
            targetFeed->updateBox(fp.lat, fp.lng);

            if (!shape) {
                shape = targetFeed->getShapes().add(ShapeT(fp.id));
            }

            if (shape) {
                if (!shape->addPoint(ShapePoint(fp.lat, fp.lng, fp.travelDist, fp.seq))) {
                    throw ParserException(
                        "shape_pt_sequence collision, shape_pt_sequence has to be increasing for a single shape.",
                        "shape_pt_sequence",
                        csvp.getCurLine());
                }
            }
        }

        targetFeed->getShapes().finalize();
    }

    // ____________________________________________________________________________
    inline bool Parser::nextStopTime(CsvParser* csvp, flat::StopTime* s, const flat::StopTimeFlds& flds) const
    {
        if (csvp->readNextLine()) {
            s->at = getTime(*csvp, flds.arrivalTimeFld);
            s->dt = getTime(*csvp, flds.departureTimeFld);

            s->trip = getString(*csvp, flds.tripIdFld);
            s->s = getString(*csvp, flds.stopIdFld);
            s->sequence = getRangeInteger(*csvp, flds.stopSequenceFld, 0, UINT32_MAX);
            s->headsign = getString(*csvp, flds.stopHeadsignFld, "");
            s->pickupType = static_cast<flat::StopTime::PU_DO_TYPE>(
                getRangeInteger(*csvp, flds.pickUpTypeFld, 0, 3, 0));
            s->dropOffType = static_cast<flat::StopTime::PU_DO_TYPE>(
                getRangeInteger(*csvp, flds.dropOffTypeFld, 0, 3, 0));

            // if at and dt are empty, default to 0 here
            s->isTimepoint = getRangeInteger(*csvp, flds.timepointFld, 0, 1, !(s->at.empty() && s->dt.empty()));

            if (s->isTimepoint && s->at.empty() && s->dt.empty()) {
                throw ParserException(
                    "if arrival_time and departure_time are empty, timepoint cannot be 1",
                    "timepoint",
                    csvp->getCurLine());
            }

            s->shapeDistTravelled = -1;    // using -1 as a null value here
            if (flds.shapeDistTraveledFld < csvp->getNumColumns()) {
                if (!getString(*csvp, flds.shapeDistTraveledFld, "").empty()) {
                    s->shapeDistTravelled = getDouble(*csvp, flds.shapeDistTraveledFld);

                    if (std::isless(s->shapeDistTravelled, -0.01)) {
                        throw ParserException(
                            "negative values not supported for distances (value was: " + std::to_string(s->shapeDistTravelled),
                            "shape_dist_traveled",
                            csvp->getCurLine());
                    }
                }
            }
            return true;
        }

        return false;
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Parser::parseStopTimes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::StopTime fst;
        auto flds = flat::StopTimeFlds::fromCsvParser(csvp);

        while (nextStopTime(&csvp, &fst, flds)) {
            StopT* stop = 0;
            TripB<StopTimeT<StopT>, ServiceT, RouteT, ShapeT>* trip = 0;

            stop = targetFeed->getStops().get(fst.s);
            trip = targetFeed->getTrips().get(fst.trip);

            if (!stop) {
                std::stringstream msg;
                msg << "no stop with id '" << fst.s << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "stop_id", csvp.getCurLine());
            }

            if (!trip) {
                std::stringstream msg;
                msg << "no trip with id '" << fst.trip
                    << "' defined in trips.txt, cannot "
                    << "reference here.";
                throw ParserException(msg.str(), "trip_id", csvp.getCurLine());
            }

            StopTimeT<StopT> st(fst.at, fst.dt, stop, fst.sequence, fst.headsign, fst.pickupType, fst.dropOffType, fst.shapeDistTravelled, fst.isTimepoint);

            if (st.getArrivalTime() > st.getDepartureTime()) {
                throw ParserException("arrival time '" + st.getArrivalTime().toString() + "' is later than departure time '" + st.getDepartureTime().toString() + "'. You cannot depart earlier than you arrive.",
                                      "departure_time",
                                      csvp.getCurLine());
            }

            if (!trip->addStopTime(st)) {
                throw ParserException(
                    "stop_sequence collision, stop_sequence has "
                    "to be increasing for a single trip.",
                    "stop_sequence",
                    csvp.getCurLine());
            }
        }
    }

    // ___________________________________________________________________________
    void Parser::fileNotFound(const std::string& file) const
    {
        throw ParserException("File not found", "", -1, std::string(file.c_str()));
    }

    // ___________________________________________________________________________
    std::string Parser::getString(const CsvParser& csv, size_t field) const
    {
        const char* r = csv.getTString(field);
        if (r[0] == 0) {
            throw ParserException("expected non-empty string", csv.getFieldName(field), csv.getCurLine());
        }
        return r;
    }

    // ___________________________________________________________________________
    std::string Parser::getString(const CsvParser& csv, size_t field, const std::string& def) const
    {
        if (field < csv.getNumColumns() && !csv.fieldIsEmpty(field)) {
            return csv.getTString(field);
        }

        return def;
    }

// ___________________________________________________________________________
    double Parser::getDouble(const CsvParser& csv, size_t field) const
    {
        return csv.getDouble(field);
    }

// ___________________________________________________________________________
    double Parser::getDouble(const CsvParser& csv, size_t field, double ret) const
    {
        if (field < csv.getNumColumns() && !csv.fieldIsEmpty(field)) {
            return csv.getDouble(field);
        }

        return ret;
    }

// ___________________________________________________________________________
    int64_t Parser::getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv) const
    {
        int64_t ret = csv.getLong(field);

        if (ret < minv || ret > maxv) {
            std::stringstream msg;
            msg << "expected integer in range [" << minv << "," << maxv << "]";
            throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }

        return ret;
    }

// ___________________________________________________________________________
    int64_t Parser::getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv, int64_t def) const
    {
        int64_t ret;

        if (field < csv.getNumColumns() && !csv.fieldIsEmpty(field)) {
            ret = csv.getLong(field);

            if (ret < minv || ret > maxv) {
                if (_strict) {
                    std::stringstream msg;
                    msg << "expected integer in range [" << minv << "," << maxv << "]";
                    throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
                } else
                    return def;
            }

            return ret;
        }

        return def;
    }

// ___________________________________________________________________________
    uint32_t Parser::getColorFromHexString(const CsvParser& csv, size_t field, const std::string& def) const
    {
        std::string color_string;

        if (field < csv.getNumColumns()) {
            color_string = csv.getTString(field);
        }

        if (color_string.empty()) color_string = def;

        size_t chars_processed = 0;
        uint32_t ret = 0;

        try {
            ret = std::stoul("0x" + color_string, &chars_processed, 16);
        } catch (const std::exception& e) {
            if (_strict) {
                std::stringstream msg;
                msg << "expected a 6-character hexadecimal color string, found '"
                    << color_string << "' instead. (Error while parsing was: " << e.what()
                    << ")";
                throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
            } else {
                return std::stoul("0x" + def, &chars_processed, 16);
            }
        }

        if (color_string.size() != 6 || chars_processed != 8) {
            if (_strict) {
                std::stringstream msg;
                msg << "expected a 6-character hexadecimal color string, found '"
                    << color_string << "' instead.";
                throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
            } else {
                return std::stoul("0x" + def, &chars_processed, 16);
            }
        }

        return ret;
    }

// ____________________________________________________________________________
    ServiceDate Parser::getServiceDate(const CsvParser& csv, size_t field) const
    {
        return getServiceDate(csv, field, false);
    }

// ____________________________________________________________________________
    ServiceDate Parser::getServiceDate(const CsvParser& csv, size_t field, bool req) const
    {
        size_t p;
        const char* val = csv.getTString(field);
        if (strlen(val) == 0 && !req) return ServiceDate();

        try {
            int32_t yyyymmdd = std::stoul(val, &p, 10);
            if (p != strlen(val) || yyyymmdd > 99999999) {
                std::stringstream msg;
                msg << "expected a date in the YYYYMMDD format, found '" << val
                    << "' instead.";
                throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
            }
            return ServiceDate(yyyymmdd);
        } catch (const std::out_of_range& e) {
            std::stringstream msg;
            msg << "expected a date in the YYYYMMDD format, found '" << val
                << "' instead. (Integer out of range).";
            throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        } catch (const std::invalid_argument& e) {
            std::stringstream msg;
            msg << "expected a date in the YYYYMMDD format, found '" << val
                << "' instead.";
            throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }
    }

// ____________________________________________________________________________
    Time Parser::getTime(const CsvParser& csv, size_t field) const
    {
        size_t p;
        const char* val = csv.getTString(field);

        if (val == nullptr || val[0] == 0) {
            return Time();
        }

        try {
            uint64_t h = std::stoul(val, &p, 10);
            if (h > 255)
                throw std::out_of_range(
                    "only hour-values up to 255 are "
                    "supported. (read "
                    + std::to_string(h) + ")");
            val += p + 1;

            uint64_t m = std::stoul(val, &p, 10);
            if (p == 1) {
                if (_strict) {
                    throw std::invalid_argument("one-digit minute values are not allowed.");
                }
            }
            // allow values of 60, although standard forbids it
            if (m > 60)
                throw std::out_of_range(
                    "only minute-values up to 60 are "
                    "allowed. (read "
                    + std::to_string(m) + ")");
            val += p + 1;

            uint64_t s = std::stoul(val, &p, 10);
            if (p == 0) s = 0;    // support HH:MM format (although standard forbids it)
            if (p == 1) {
                if (_strict) {
                    throw std::invalid_argument("one-digit second values are not allowed.");
                }
            }
            // allow values of 60, although standard forbids it
            if (s > 60)
                throw std::out_of_range(
                    "only second-values up to 60 are "
                    "allowed. (read "
                    + std::to_string(s) + ")");

            return Time(h, m % 60, s % 60);
        } catch (const std::exception& e) {
            std::stringstream msg;
            msg << "expected a time in HH:MM:SS (or H:MM:SS) format, found '" << val
                << "' instead. (" << e.what() << ")";
            throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }
    }

    // ____________________________________________________________________________
    flat::Route::TYPE Parser::getRouteType(const CsvParser& csv, size_t field, int64_t tn) const
    {
        auto t = flat::Route::getRouteType(tn);
        if (t == flat::Route::NONE) {
            std::stringstream msg;
            msg << "route type '" << tn << "' not supported.";
            throw ParserException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }
        return t;
    }

}    // namespace ad::cppgtfs

#endif    // AD_CPPGTFS_PARSER_H_
