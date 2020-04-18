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

#include "csv/CsvParser.h"
#include "cppgtfs/DataExtractor.h"
#include "cppgtfs/gtfs/Feed.h"
#include "cppgtfs/gtfs/Frequency.h"
#include "cppgtfs/gtfs/Route.h"
#include "cppgtfs/gtfs/Service.h"
#include "cppgtfs/gtfs/Shape.h"
#include "cppgtfs/gtfs/Transfer.h"
#include "cppgtfs/gtfs/StopTime.h"
#include "cppgtfs/exceptions/ParseException.h"
#include "cppgtfs/exceptions/FileNotFoundException.h"
#include <cppgtfs/gtfs/Model.h>

using namespace cppgtfs::gtfs;
using namespace csv;


// A GTFS parser
namespace cppgtfs
{
    using namespace exceptions;

    class ReaderBase
    {
    public:
        ReaderBase(bool strict);

        // ____________________________________________________________________________
        bool nextShapePoint(CsvParser& csvp, ShapePointFlat* c, const ShapeFields& flds) const;

        // ____________________________________________________________________________
        bool nextStopTime(CsvParser& csvp, StopTime::Flat* s, const StopTime::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextTransfer(CsvParser& csvp, TransferFlat* t, const TransfersFields& flds) const;

        // ____________________________________________________________________________
        bool nextFrequency(CsvParser& csvp, Frequency::Flat* r, const Frequency::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextFare(CsvParser& csvp, Fare::Flat* t, const Fare::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextFareRule(CsvParser& csvp, FareRule::Flat* t, const FareRule::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextAgency(CsvParser& csvp, gtfs::Agency::Flat* a, const gtfs::Agency::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextStop(CsvParser& csvp, Stop::Flat* s, const Stop::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextRoute(CsvParser& csvp, Route::Flat* r, const Route::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextCalendar(CsvParser& csvp, CalendarFlat* c, const CalendarFields& flds) const;

        // ____________________________________________________________________________
        bool nextCalendarDate(CsvParser& csvp, CalendarDateFlat* c, const CalendarDateFields& flds) const;

        // ____________________________________________________________________________
        bool nextTrip(CsvParser& csvp, TripFlat* c, const TripFields& flds) const;

    protected:
        DataExtractor _dataExtractor;
    };


    class Reader : public ReaderBase
    {
    public:
        // Default initialization.
        Reader(const std::string& path);

        explicit Reader(const std::string& path, bool strict);

        // parse a zip/folder into a GtfsFeed
        FEEDTPL
        bool parse(FEEDB& targetFeed) const;

        FEEDTPL
        void parseAgencies(FEEDB& targetFeed) const;

        FEEDTPL
        void parseStops(FEEDB& targetFeed) const;

        FEEDTPL
        void parseRoutes(FEEDB& targetFeed) const;

        FEEDTPL
        void parseTrips(FEEDB& targetFeed) const;

        FEEDTPL
        void parseStopTimes(FEEDB& targetFeed) const;

        FEEDTPL
        void parseCalendar(FEEDB& targetFeed) const;

        FEEDTPL
        void parseCalendarDates(FEEDB& targetFeed) const;

        FEEDTPL
        void parseFareAttributes(FEEDB& targetFeed) const;

        FEEDTPL
        void parseFareRules(FEEDB& targetFeed) const;

        FEEDTPL
        void parseShapes(FEEDB& targetFeed) const;

        FEEDTPL
        void parseFrequencies(FEEDB& targetFeed) const;

        FEEDTPL
        void parseTransfers(FEEDB& targetFeed) const;

        FEEDTPL
        void parseFeedInfo(FEEDB& targetFeed) const;

    private:
        std::string _path;

        FEEDTPL
        void parseAgencies(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseStops(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseRoutes(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseTrips(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseStopTimes(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseCalendar(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseCalendarDates(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseFareAttributes(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseFareRules(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseShapes(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseFrequencies(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseTransfers(FEEDB& targetFeed, std::istream*) const;

        FEEDTPL
        void parseFeedInfo(FEEDB& targetFeed, std::istream*) const;
    };


    // ____________________________________________________________________________
    FEEDTPL
    bool Reader::parse(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseTransfers(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseFrequencies(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseFareAttributes(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseFareRules(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseFeedInfo(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseAgencies(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseStops(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseRoutes(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseCalendar(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseCalendarDates(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseTrips(FEEDB& targetFeed, std::istream* s) const
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
    FEEDTPL
    void Reader::parseStops(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseRoutes(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseCalendar(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseCalendarDates(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseFeedInfo(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseAgencies(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseShapes(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseTrips(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseStopTimes(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseFareRules(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseFareAttributes(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseTransfers(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseFrequencies(FEEDB& targetFeed) const
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
    FEEDTPL
    void Reader::parseShapes(FEEDB& targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        ShapePointFlat fp;
        auto flds = ShapeFields::fromCsvParser(csvp);

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
    FEEDTPL
    void Reader::parseStopTimes(FEEDB& targetFeed, std::istream* s) const
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

#endif    // AD_CPPGTFS_PARSER_H_
