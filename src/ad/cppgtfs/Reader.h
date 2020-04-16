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
#include "ad/cppgtfs/exceptions/ParseException.h"
#include "ad/cppgtfs/DataExtractor.h"
#include "ad/cppgtfs/exceptions/FileNotFoundException.h"


using namespace ad::cppgtfs::gtfs;
using namespace ad::util;

// A GTFS parser
namespace ad::cppgtfs
{
    using namespace exceptions;

    class ReaderBase
    {
    public:
        ReaderBase(bool strict);

        // ____________________________________________________________________________
        bool nextShapePoint(CsvParser& csvp, flat::ShapePoint* c, const flat::ShapeFlds& flds) const;

        // ____________________________________________________________________________
        bool nextStopTime(CsvParser& csvp, flat::StopTime* s, const flat::StopTimeFlds& flds) const;

        // ____________________________________________________________________________
        bool nextTransfer(CsvParser& csvp, flat::Transfer* t, const flat::TransfersFlds& flds) const;

        // ____________________________________________________________________________
        bool nextFrequency(CsvParser& csvp, flat::Frequency* r, const flat::FrequencyFlds& flds) const;

        // ____________________________________________________________________________
        bool nextFare(CsvParser& csvp, flat::Fare* t, const flat::FareFlds& flds) const;

        // ____________________________________________________________________________
        bool nextFareRule(CsvParser& csvp, flat::FareRule* t, const flat::FareRuleFlds& flds) const;

        // ____________________________________________________________________________
        bool nextAgency(CsvParser& csvp, flat::Agency* a, const flat::AgencyFlds& flds) const;

        // ____________________________________________________________________________
        bool nextStop(CsvParser& csvp, flat::Stop* s, const flat::StopFlds& flds) const;

        // ____________________________________________________________________________
        bool nextRoute(CsvParser& csvp, flat::Route* r, const flat::RouteFlds& flds) const;

        // ____________________________________________________________________________
        bool nextCalendar(CsvParser& csvp, flat::Calendar* c, const flat::CalendarFlds& flds) const;

        // ____________________________________________________________________________
        bool nextCalendarDate(CsvParser& csvp, flat::CalendarDate* c, const flat::CalendarDateFlds& flds) const;

        // ____________________________________________________________________________
        bool nextTrip(CsvParser& csvp, flat::Trip* c, const flat::TripFlds& flds) const;

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
        bool parse(FEEDB* targetFeed) const;

        FEEDTPL
        void parseAgencies(FEEDB* targetFeed) const;

        FEEDTPL
        void parseStops(FEEDB* targetFeed) const;

        FEEDTPL
        void parseRoutes(FEEDB* targetFeed) const;

        FEEDTPL
        void parseTrips(FEEDB* targetFeed) const;

        FEEDTPL
        void parseStopTimes(FEEDB* targetFeed) const;

        FEEDTPL
        void parseCalendar(FEEDB* targetFeed) const;

        FEEDTPL
        void parseCalendarDates(FEEDB* targetFeed) const;

        FEEDTPL
        void parseFareAttributes(FEEDB* targetFeed) const;

        FEEDTPL
        void parseFareRules(FEEDB* targetFeed) const;

        FEEDTPL
        void parseShapes(FEEDB* targetFeed) const;

        FEEDTPL
        void parseFrequencies(FEEDB* targetFeed) const;

        FEEDTPL
        void parseTransfers(FEEDB* targetFeed) const;

        FEEDTPL
        void parseFeedInfo(FEEDB* targetFeed) const;

    private:
        std::string _path;

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
    bool Reader::parse(FEEDB* targetFeed) const
    {
        std::ifstream fs;
        std::string curFile;

        targetFeed->setPath(_path);

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
    void Reader::parseTransfers(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Transfer ft;
        auto flds = flat::TransfersFlds::fromCsvParser(csvp);

        while (nextTransfer(csvp, &ft, flds)) {
            StopT* fromStop = targetFeed->getStops().get(ft.fromStop);
            StopT* toStop = targetFeed->getStops().get(ft.toStop);

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
            targetFeed->getTransfers().push_back(t);
        }
    }



// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseFrequencies(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Frequency ff;
        auto flds = flat::FrequencyFlds::fromCsvParser(csvp);

        while (nextFrequency(csvp, &ff, flds)) {
            Frequency f(ff.startTime, ff.endTime, ff.headwaySecs, ff.exactTimes);

            auto trip = targetFeed->getTrips().get(ff.tripId);
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
    void Reader::parseFareAttributes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Fare ff;
        auto flds = flat::FareFlds::fromCsvParser(csvp);

        while (nextFare(csvp, &ff, flds)) {
            typename AgencyT::Ref agency = typename AgencyT::Ref();

            if (!ff.agency.empty()) {
                agency = targetFeed->getAgencies().get(ff.agency);
                if (!agency) {
                    std::stringstream msg;
                    msg << "no agency with id '" << ff.agency << "' defined, cannot "
                        << "reference here.";
                    throw ParseException(msg.str(), "agency_id", csvp.getCurLine());
                }
            }

            targetFeed->getFares().add(FareT<RouteT>(ff.id, ff.price, ff.currencyType, ff.paymentMethod, ff.numTransfers, agency, ff.duration));
        }
    }

// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseFareRules(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::FareRule fr;
        auto flds = flat::FareRuleFlds::fromCsvParser(csvp);

        while (nextFareRule(csvp, &fr, flds)) {
            Fare<RouteT>* fare = targetFeed->getFares().get(fr.fare);
            RouteT* route = targetFeed->getRoutes().get(fr.route);

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

            if (!fr.originZone.empty() && !targetFeed->getZones().count(fr.originZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.originZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "origin_id", csvp.getCurLine());
            }

            if (!fr.destZone.empty() && !targetFeed->getZones().count(fr.destZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.destZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "destination_id", csvp.getCurLine());
            }

            if (!fr.containsZone.empty() && !targetFeed->getZones().count(fr.containsZone)) {
                std::stringstream msg;
                msg << "no zone with id '" << fr.containsZone
                    << "' defined in stops.txt, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "contains_id", csvp.getCurLine());
            }

            FareRule<RouteT> r(route, fr.originZone, fr.destZone, fr.containsZone);
            fare->addFareRule(r);
        }

        targetFeed->getFares().finalize();
    }

// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseFeedInfo(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        size_t feedPublisherNameFld = csvp.getFieldIndex("feed_publisher_name");
        size_t feedPublisherUrlFld = csvp.getFieldIndex("feed_publisher_url");
        size_t feedLangFld = csvp.getOptFieldIndex("feed_lang");
        size_t feedStartDateFld = csvp.getOptFieldIndex("feed_start_date");
        size_t feedEndDateFld = csvp.getOptFieldIndex("feed_end_date");
        size_t feedVersionFld = csvp.getOptFieldIndex("feed_version");

        while (csvp.readNextLine()) {
            targetFeed->setPublisherName(_dataExtractor.getString(csvp, feedPublisherNameFld));
            targetFeed->setPublisherUrl(_dataExtractor.getString(csvp, feedPublisherUrlFld));
            targetFeed->setLang(_dataExtractor.getString(csvp, feedLangFld, ""));
            targetFeed->setVersion(_dataExtractor.getString(csvp, feedVersionFld, ""));
            targetFeed->setStartDate(_dataExtractor.getServiceDate(csvp, feedStartDateFld, false));
            targetFeed->setEndDate(_dataExtractor.getServiceDate(csvp, feedEndDateFld, false));
        }
    }



// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseAgencies(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);
        typename AgencyT::Ref a = (typename AgencyT::Ref());
        flat::Agency fa;
        auto flds = flat::AgencyFlds::fromCsvParser(csvp);

        while (nextAgency(csvp, &fa, flds)) {
            if ((typename AgencyT::Ref()) == (a = targetFeed->getAgencies().add(Agency(fa.id, fa.name, fa.url, fa.timezone, fa.lang, fa.phone, fa.fare_url, fa.agency_email)))) {
                std::stringstream msg;
                msg << "'agency_id' must be dataset unique. Collision with id '"<< a->getId() << "')";
                throw ParseException(msg.str(), "agency_id", csvp.getCurLine());
            }
        }

        if ((typename AgencyT::Ref()) == a) {
            throw ParseException("the feed has no agency defined. This is a required field.","",1);
        }

        targetFeed->getAgencies().finalize();
    }



// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseStops(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        std::map<std::string, std::pair<size_t, std::string>> parentStations;

        flat::Stop fs;
        auto flds = flat::StopFlds::fromCsvParser(csvp);

        while (nextStop(csvp, &fs, flds)) {
            targetFeed->updateBox(fs.lat, fs.lng);

            const StopT& stop =
                StopT(fs.id, fs.code, fs.name, fs.desc, fs.lat, fs.lng, fs.zone_id, fs.stop_url, fs.location_type, 0, fs.stop_timezone, fs.wheelchair_boarding, fs.platform_code);

            if (!fs.parent_station.empty()) {
                if (fs.location_type == flat::Stop::LOCATION_TYPE::STATION) {
                    throw ParseException(
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
                throw ParseException(msg.str(), "stop_id", csvp.getCurLine());
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
                throw ParseException(msg.str(), "parent_station", ps.second.first);
            } else {
                targetFeed->getStops().get(ps.first)->setParentStation(parentStation);
            }
        }
    }



// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseRoutes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Route fr;
        auto flds = flat::RouteFlds::fromCsvParser(csvp);

        while (nextRoute(csvp, &fr, flds)) {
            typename AgencyT::Ref routeAgency = 0;

            if (!fr.agency.empty()) {
                routeAgency = targetFeed->getAgencies().get(fr.agency);
                if ((typename AgencyT::Ref()) == routeAgency) {
                    std::stringstream msg;
                    msg << "no agency with id '" << fr.agency << "' defined, cannot "
                        << "reference here.";
                    throw ParseException(msg.str(), "agency_id", csvp.getCurLine());
                }
            }

            if (!targetFeed->getRoutes().add(RouteT(fr.id, routeAgency, fr.short_name, fr.long_name, fr.desc, fr.type, fr.url, fr.color, fr.text_color))) {
                std::stringstream msg;
                msg << "'route_id' must be dataset unique. Collision with id '" << fr.id
                    << "')";
                throw ParseException(msg.str(), "route_id", csvp.getCurLine());
            }
        }

        targetFeed->getRoutes().finalize();
    }



// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseCalendar(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Calendar fc;
        auto flds = flat::CalendarFlds::fromCsvParser(csvp);

        while (nextCalendar(csvp, &fc, flds)) {
            if ((typename ServiceT::Ref()) == targetFeed->getServices().add(ServiceT(fc.id, fc.serviceDays, fc.begin, fc.end))) {
                std::stringstream msg;
                msg << "'service_id' must be unique in calendars.txt. Collision with id '"
                    << fc.id << "')";
                throw ParseException(msg.str(), "service_id", csvp.getCurLine());
            }
        }
    }



// ____________________________________________________________________________
    FEEDTPL
    void Reader::parseCalendarDates(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::CalendarDate fc;
        auto flds = flat::CalendarDateFlds::fromCsvParser(csvp);

        while (nextCalendarDate(csvp, &fc, flds)) {
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
    FEEDTPL
    void Reader::parseTrips(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::Trip ft;
        auto flds = flat::TripFlds::fromCsvParser(csvp);

        while (nextTrip(csvp, &ft, flds)) {
            RouteT* tripRoute = 0;

            tripRoute = targetFeed->getRoutes().get(ft.route);
            if (!tripRoute) {
                std::stringstream msg;
                msg << "no route with id '" << ft.route << "' defined, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "route_id", csvp.getCurLine());
            }

            typename ShapeT::Ref tripShape = (typename ShapeT::Ref());

            if (!ft.shape.empty()) {
                tripShape = targetFeed->getShapes().getRef(ft.shape);
                if (tripShape == (typename ShapeT::Ref())) {
                    std::stringstream msg;
                    msg << "no shape with id '" << ft.shape << "' defined, cannot "
                        << "reference here.";
                    throw ParseException(msg.str(), "shape_id", csvp.getCurLine());
                }
            }

            typename ServiceT::Ref tripService =
                targetFeed->getServices().getRef(ft.service);

            if ((typename ServiceT::Ref()) == tripService) {
                std::stringstream msg;
                msg << "no service with id '" << ft.service << "' defined, cannot "
                    << "reference here.";
                throw ParseException(msg.str(), "service_id", csvp.getCurLine());
            }

            if (typename TripB<StopTimeT<StopT>, ServiceT, RouteT, ShapeT>::Ref() == targetFeed->getTrips().add(TripB<StopTimeT<StopT>, ServiceT, RouteT, ShapeT>(ft.id, tripRoute, tripService, ft.headsign, ft.short_name, ft.dir, ft.block_id, tripShape, ft.wc, ft.ba))) {
                std::stringstream msg;
                msg << "'trip_id' must be dataset unique. Collision with id '"
                    << _dataExtractor.getString(csvp, flds.tripIdFld) << "')";
                throw ParseException(msg.str(), "trip_id", csvp.getCurLine());
            }
        }

        targetFeed->getTrips().finalize();
    }


    // ____________________________________________________________________________
    FEEDTPL
    void Reader::parseStops(FEEDB* targetFeed) const
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
    void Reader::parseRoutes(FEEDB* targetFeed) const
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
    void Reader::parseCalendar(FEEDB* targetFeed) const
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
    void Reader::parseCalendarDates(FEEDB* targetFeed) const
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
    void Reader::parseFeedInfo(FEEDB* targetFeed) const
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
    void Reader::parseAgencies(FEEDB* targetFeed) const
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
    void Reader::parseShapes(FEEDB* targetFeed) const
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
    void Reader::parseTrips(FEEDB* targetFeed) const
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
    void Reader::parseStopTimes(FEEDB* targetFeed) const
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
    void Reader::parseFareRules(FEEDB* targetFeed) const
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
    void Reader::parseFareAttributes(FEEDB* targetFeed) const
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
    void Reader::parseTransfers(FEEDB* targetFeed) const
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
    void Reader::parseFrequencies(FEEDB* targetFeed) const
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
    void Reader::parseShapes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::ShapePoint fp;
        auto flds = flat::ShapeFlds::fromCsvParser(csvp);

        while (nextShapePoint(csvp, &fp, flds)) {
            auto shape = targetFeed->getShapes().get(fp.id);
            targetFeed->updateBox(fp.lat, fp.lng);

            if (!shape) {
                shape = targetFeed->getShapes().add(ShapeT(fp.id));
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

        targetFeed->getShapes().finalize();
    }

    // ____________________________________________________________________________
    FEEDTPL
    void Reader::parseStopTimes(FEEDB* targetFeed, std::istream* s) const
    {
        CsvParser csvp(s);

        flat::StopTime fst;
        auto flds = flat::StopTimeFlds::fromCsvParser(csvp);

        while (nextStopTime(csvp, &fst, flds)) {
            StopT* stop = 0;
            TripB<StopTimeT<StopT>, ServiceT, RouteT, ShapeT>* trip = 0;

            stop = targetFeed->getStops().get(fst.s);
            trip = targetFeed->getTrips().get(fst.trip);

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

            StopTimeT<StopT> st(fst.at, fst.dt, stop, fst.sequence, fst.headsign, fst.pickupType, fst.dropOffType, fst.shapeDistTravelled, fst.isTimepoint);

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

}    // namespace ad::cppgtfs

#endif    // AD_CPPGTFS_PARSER_H_