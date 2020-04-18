// Copyright 2018, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#include <cppgtfs/Writer.h>
#include <csv/CsvWriter.h>
#include <cppgtfs/gtfs/Shape.h>
#include <cppgtfs/gtfs/Trip.h>
#include <cppgtfs/gtfs/Service.h>
#include <cppgtfs/gtfs/StopTime.h>
#include <cppgtfs/gtfs/Transfer.h>
#include <cppgtfs/exceptions/WriteException.h>

#include <fstream>
#include <map>
#include <string>
#include <utility>

using cppgtfs::Writer;
using cppgtfs::gtfs::Agency;
using cppgtfs::gtfs::Route;
using cppgtfs::gtfs::Service;
using cppgtfs::gtfs::ServiceDate;
using cppgtfs::gtfs::Shape;
using cppgtfs::gtfs::ShapePoint;
using cppgtfs::gtfs::Stop;
using cppgtfs::gtfs::StopTime;
using cppgtfs::gtfs::Time;
using cppgtfs::gtfs::Trip;
using csv::CsvWriter;

// ____________________________________________________________________________
bool Writer::write(gtfs::Feed* sourceFeed, const std::string& path) const
{
    std::ofstream fs;
    std::string gtfsPath(path);
    std::string curFile;

    curFile = gtfsPath + "/shapes.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    writeShapes(sourceFeed, &fs);
    fs.close();

    curFile = gtfsPath + "/trips.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    bool hasFreqs = writeTrips(sourceFeed, &fs);
    fs.close();

    curFile = gtfsPath + "/agency.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    writeAgencies(sourceFeed, &fs);
    fs.close();

    curFile = gtfsPath + "/stops.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    writeStops(sourceFeed, &fs);
    fs.close();

    curFile = gtfsPath + "/stop_times.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    writeStopTimes(sourceFeed, &fs);
    fs.close();

    curFile = gtfsPath + "/routes.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    writeRoutes(sourceFeed, &fs);
    fs.close();

    if (!sourceFeed->getPublisherUrl().empty() && !sourceFeed->getPublisherName().empty()) {
        curFile = gtfsPath + "/feed_info.txt";
        fs.open(curFile.c_str());
        if (!fs.good()) cannotWrite(curFile);
        writeFeedInfo(sourceFeed, &fs);
        fs.close();
    }

    curFile = gtfsPath + "/calendar.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    writeCalendars(sourceFeed, &fs);
    fs.close();

    curFile = gtfsPath + "/calendar_dates.txt";
    fs.open(curFile.c_str());
    if (!fs.good()) cannotWrite(curFile);
    writeCalendarDates(sourceFeed, &fs);
    fs.close();

    if (hasFreqs) {
        curFile = gtfsPath + "/frequencies.txt";
        fs.open(curFile.c_str());
        if (!fs.good()) cannotWrite(curFile);
        writeFrequencies(sourceFeed, &fs);
        fs.close();
    }

    if (sourceFeed->getTransfers().size()) {
        curFile = gtfsPath + "/transfers.txt";
        fs.open(curFile.c_str());
        if (!fs.good()) cannotWrite(curFile);
        writeTransfers(sourceFeed, &fs);
        fs.close();
    }

    if (sourceFeed->getFares().size()) {
        curFile = gtfsPath + "/fare_attributes.txt";
        fs.open(curFile.c_str());
        if (!fs.good()) cannotWrite(curFile);
        writeFares(sourceFeed, &fs);
        fs.close();

        curFile = gtfsPath + "/fare_rules.txt";
        fs.open(curFile.c_str());
        if (!fs.good()) cannotWrite(curFile);
        writeFareRules(sourceFeed, &fs);
        fs.close();
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getAgencyCsvw(std::ostream* os)
{
    return CsvWriter(
        os, { "agency_id", "agency_name", "agency_url", "agency_timezone", "agency_lang", "agency_phone", "agency_fare_url", "agency_email" });
}

// ____________________________________________________________________________
bool Writer::writeAgency(const gtfs::Agency::Flat& ag, CsvWriter* csvw) const
{
    csvw->writeString(ag.id);
    csvw->writeString(ag.name);
    csvw->writeString(ag.url);
    csvw->writeString(ag.timezone);
    csvw->writeString(ag.lang);
    csvw->writeString(ag.phone);
    csvw->writeString(ag.fare_url);
    csvw->writeString(ag.agency_email);
    csvw->flushLine();

    return true;
}

// ____________________________________________________________________________
bool Writer::writeAgencies(gtfs::Feed* sourceFeed, std::ostream* s) const
{
    CsvWriter csvw = getAgencyCsvw(s);
    for (const auto& a : sourceFeed->getAgencies()) {
        writeAgency(a.second->getFlat(), &csvw);
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getStopsCsvw(std::ostream* os)
{
    return CsvWriter(
        os, { "stop_id", "stop_code", "stop_name", "stop_desc", "stop_lat", "stop_lon", "zone_id", "stop_url", "location_type", "parent_station", "stop_timezone", "wheelchair_boarding", "platform_code" });
}

// ____________________________________________________________________________
bool Writer::writeStop(const gtfs::Stop::Flat& s, CsvWriter* csvw) const
{
    csvw->writeString(s.id);
    csvw->writeString(s.code);
    csvw->writeString(s.name);
    csvw->writeString(s.desc);
    csvw->writeDouble(s.lat);
    csvw->writeDouble(s.lng);
    csvw->writeString(s.zone_id);
    csvw->writeString(s.stop_url);
    csvw->writeInt(s.location_type);
    if (!s.parent_station.empty())
        csvw->writeString(s.parent_station);
    else
        csvw->skip();
    csvw->writeString(s.stop_timezone);
    csvw->writeInt(s.wheelchair_boarding);
    csvw->writeString(s.platform_code);
    csvw->flushLine();

    return true;
}

// ____________________________________________________________________________
bool Writer::writeStops(gtfs::Feed* sourceFeed, std::ostream* s) const
{
    CsvWriter csvw = getStopsCsvw(s);

    for (const auto& t : sourceFeed->getStops()) {
        writeStop(t.second->getFlat(), &csvw);
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getTripsCsvw(std::ostream* os)
{
    return CsvWriter(os, { "route_id", "service_id", "trip_id", "trip_headsign", "trip_short_name", "direction_id", "block_id", "shape_id", "wheelchair_accessible", "bikes_allowed" });
}

// ____________________________________________________________________________
bool Writer::writeTrip(const gtfs::TripFlat& t, CsvWriter* csvw) const
{
    csvw->writeString(t.route);
    csvw->writeString(t.service);
    csvw->writeString(t.id);
    csvw->writeString(t.headsign);
    csvw->writeString(t.short_name);
    if (t.dir < 2)
        csvw->writeInt(t.dir);
    else
        csvw->skip();
    csvw->writeString(t.block_id);
    if (!t.shape.empty())
        csvw->writeString(t.shape);
    else
        csvw->skip();
    csvw->writeInt(t.wc);
    csvw->writeInt(t.ba);
    csvw->flushLine();
    return true;
}

// ____________________________________________________________________________
bool Writer::writeTrips(gtfs::Feed* sourceFeed, std::ostream* s) const
{
    bool hasFreqs = false;
    CsvWriter csvw = getTripsCsvw(s);
    for (const auto& t : sourceFeed->getTrips()) {
        if (t.second->getFrequencies().size()) hasFreqs = true;
        writeTrip(t.second->getFlat(), &csvw);
    }

    return hasFreqs;
}

// ____________________________________________________________________________
CsvWriter Writer::getStopTimesCsvw(std::ostream* os)
{
    return CsvWriter(os, { "trip_id", "arrival_time", "departure_time", "stop_id", "stop_sequence", "stop_headsign", "pickup_type", "drop_off_type", "shape_dist_traveled", "timepoint" });
}

// ____________________________________________________________________________
bool Writer::writeStopTime(const gtfs::StopTime::Flat& st,
    CsvWriter* csvw) const
{
    csvw->writeString(st.trip);
    csvw->writeString(st.at.toString());
    csvw->writeString(st.dt.toString());
    csvw->writeString(st.s);
    csvw->writeInt(st.sequence);
    csvw->writeString(st.headsign);
    csvw->writeInt(st.pickupType);
    csvw->writeInt(st.dropOffType);
    if (st.shapeDistTravelled > -.5)
        csvw->writeDouble(st.shapeDistTravelled);
    else
        csvw->skip();
    csvw->writeInt(st.isTimepoint);
    csvw->flushLine();
    return true;
}

// ____________________________________________________________________________
bool Writer::writeStopTimes(gtfs::Feed* sourceFeed, std::ostream* s) const
{
    CsvWriter csvw = getStopTimesCsvw(s);

    for (const auto& t : sourceFeed->getTrips()) {
        for (const auto& p : t.second->getStopTimes()) {
            writeStopTime(
                gtfs::StopTime::Flat{ p.getArrivalTime(), p.getDepartureTime(), t.second->getId(), p.getStop()->getId(), p.getSeq(), p.getHeadsign(), p.getPickupType(), p.getDropOffType(), p.isTimepoint(), p.getShapeDistanceTravelled() },
                &csvw);
        }
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getShapesCsvw(std::ostream* os)
{
    return CsvWriter(os, { "shape_id", "shape_pt_lat", "shape_pt_lon", "shape_pt_sequence", "shape_dist_traveled" });
}

// ____________________________________________________________________________
bool Writer::writeShapePoint(const gtfs::ShapePointFlat& s,
    CsvWriter* csvw) const
{
    csvw->writeString(s.id);
    csvw->writeDouble(s.lat);
    csvw->writeDouble(s.lng);
    csvw->writeInt(s.seq);
    if (s.travelDist > -0.5)
        csvw->writeDouble(s.travelDist);
    else
        csvw->skip();
    csvw->flushLine();
    return true;
}

// ____________________________________________________________________________
bool Writer::writeShapes(gtfs::Feed* sourceFeed, std::ostream* s) const
{
    CsvWriter csvw = getShapesCsvw(s);
    csvw.flushLine();
    for (const auto& t : sourceFeed->getShapes()) {
        for (const auto& p : t.second->getPoints()) {
            writeShapePoint(gtfs::ShapePointFlat{ t.second->getId(), p.lat, p.lng, p.travelDist, p.seq },
                &csvw);
        }
    }

    return true;
}

// ____________________________________________________________________________
bool Writer::writeRoute(const gtfs::Route::Flat& s, CsvWriter* csvw) const
{
    csvw->writeString(s.id);
    if (!s.agency.empty())
        csvw->writeString(s.agency);
    else
        csvw->skip();
    csvw->writeString(s.short_name);
    csvw->writeString(s.long_name);
    csvw->writeString(s.desc);
    csvw->writeInt(static_cast<int>(s.type));
    csvw->writeString(s.url);
    csvw->writeString(gtfs::Route::Flat::getHexColorString(s.color));
    csvw->writeString(gtfs::Route::Flat::getHexColorString(s.text_color));
    csvw->flushLine();

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getRoutesCsvw(std::ostream* os)
{
    return CsvWriter(os, { "route_id", "agency_id", "route_short_name", "route_long_name", "route_desc", "route_type", "route_url", "route_color", "route_text_color" });
}

// ____________________________________________________________________________
bool Writer::writeRoutes(gtfs::Feed* sourceFeed, std::ostream* s) const
{
    CsvWriter csvw = getAgencyCsvw(s);
    csvw.flushLine();
    for (const auto& a : sourceFeed->getRoutes()) {
        writeRoute(a.second->getFlat(), &csvw);
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getFeedInfoCsvw(std::ostream* os)
{
    return CsvWriter(os, { "feed_publisher_name", "feed_publisher_url", "feed_lang", "feed_start_date", "feed_end_date", "feed_version" });
}

// ____________________________________________________________________________
bool Writer::writeFeedInfo(gtfs::Feed* f, std::ostream* os) const
{
    auto csvw = getFeedInfoCsvw(os);
    csvw.flushLine();
    csvw.writeString(f->getPublisherName());
    csvw.writeString(f->getPublisherUrl());
    csvw.writeString(f->getLang());
    if (!f->getStartDate().empty())
        csvw.writeInt(f->getStartDate().getYYYYMMDD());
    else
        csvw.skip();
    if (!f->getEndDate().empty())
        csvw.writeInt(f->getEndDate().getYYYYMMDD());
    else
        csvw.skip();
    csvw.writeString(f->getVersion());
    csvw.flushLine();

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getTransfersCsvw(std::ostream* os)
{
    return CsvWriter(
        os, { "from_stop_id", "to_stop_id", "transfer_type", "min_transfer_time" });
}

// ____________________________________________________________________________
bool Writer::writeTransfer(const gtfs::TransferFlat& t,
    CsvWriter* csvw) const
{
    csvw->writeString(t.fromStop);
    csvw->writeString(t.toStop);
    csvw->writeInt(t.type);
    if (t.tTime > -1)
        csvw->writeInt(t.tTime);
    else
        csvw->skip();
    csvw->flushLine();
    return true;
}

// ____________________________________________________________________________
bool Writer::writeTransfers(gtfs::Feed* f, std::ostream* os) const
{
    auto csvw = getTransfersCsvw(os);
    csvw.flushLine();

    for (const auto& t : f->getTransfers()) {
        writeTransfer(t.getFlat(), &csvw);
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getFaresCsvw(std::ostream* os)
{
    return CsvWriter(os, { "fare_id", "price", "currency_type", "payment_method", "transfers", "agency_id", "transfer_duration" });
}

// ____________________________________________________________________________
bool Writer::writeFare(const gtfs::Fare::Flat& t, CsvWriter* csvw) const
{
    csvw->writeString(t.id);
    csvw->writeDouble(t.price);
    csvw->writeString(t.currencyType);
    csvw->writeInt(t.paymentMethod);
    csvw->writeInt(t.numTransfers);
    if (!t.agency.empty())
        csvw->writeString(t.agency);
    else
        csvw->skip();
    if (t.duration > -1)
        csvw->writeInt(t.duration);
    else
        csvw->skip();
    csvw->flushLine();
    return true;
}

// ____________________________________________________________________________
bool Writer::writeFares(gtfs::Feed* f, std::ostream* os) const
{
    auto csvw = getFaresCsvw(os);
    csvw.flushLine();

    for (const auto& r : f->getFares()) {
        writeFare(r.second->getFlat(), &csvw);
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getFareRulesCsvw(std::ostream* os)
{
    return CsvWriter(os, { "fare_id", "route_id", "origin_id", "destination_id", "contains_id" });
}

// ____________________________________________________________________________
bool Writer::writeFareRule(const gtfs::FareRule::Flat& t,
    CsvWriter* csvw) const
{
    csvw->writeString(t.fare);
    if (!t.route.empty())
        csvw->writeString(t.route);
    else
        csvw->skip();
    if (!t.originZone.empty())
        csvw->writeString(t.originZone);
    else
        csvw->skip();
    if (!t.destZone.empty())
        csvw->writeString(t.destZone);
    else
        csvw->skip();
    if (!t.containsZone.empty())
        csvw->writeString(t.containsZone);
    else
        csvw->skip();
    csvw->flushLine();
    return true;
}

// ____________________________________________________________________________
bool Writer::writeFareRules(gtfs::Feed* f, std::ostream* os) const
{
    auto csvw = getFareRulesCsvw(os);
    csvw.flushLine();

    for (const auto& fare : f->getFares()) {
        for (const auto& r : fare.second->getFareRules()) {
            writeFareRule(
                gtfs::FareRule::Flat{
                    fare.second->getId(), r.getRoute() ? r.getRoute()->getId() : "", r.getOriginId(), r.getDestId(), r.getContainsId() },
                &csvw);
        }
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getCalendarCsvw(std::ostream* os)
{
    return CsvWriter(
        os, { "service_id", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", "start_date", "end_date" });
}

// ____________________________________________________________________________
bool Writer::writeCalendar(const gtfs::CalendarFlat& s, CsvWriter* csvw) const
{
    csvw->writeString(s.id);
    csvw->writeInt(static_cast<bool>(s.serviceDays & gtfs::Service::SERVICE_DAY::MONDAYS));
    csvw->writeInt(static_cast<bool>(s.serviceDays & gtfs::Service::SERVICE_DAY::TUESDAYS));
    csvw->writeInt(static_cast<bool>(s.serviceDays & gtfs::Service::SERVICE_DAY::WEDNESDAYS));
    csvw->writeInt(static_cast<bool>(s.serviceDays & gtfs::Service::SERVICE_DAY::THURSDAYS));
    csvw->writeInt(static_cast<bool>(s.serviceDays & gtfs::Service::SERVICE_DAY::FRIDAYS));
    csvw->writeInt(static_cast<bool>(s.serviceDays & gtfs::Service::SERVICE_DAY::SATURDAYS));
    csvw->writeInt(static_cast<bool>(s.serviceDays & gtfs::Service::SERVICE_DAY::SUNDAYS));
    csvw->writeInt(s.begin.getYYYYMMDD());
    csvw->writeInt(s.end.getYYYYMMDD());
    csvw->flushLine();

    return true;
}

// ____________________________________________________________________________
bool Writer::writeCalendars(gtfs::Feed* f, std::ostream* os) const
{
    auto csvw = getCalendarCsvw(os);
    csvw.flushLine();
    for (const auto& r : f->getServices()) {
        if (!r.second->hasServiceDays()) continue;
        writeCalendar(r.second->getFlat(), &csvw);
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getCalendarDatesCsvw(std::ostream* os)
{
    return CsvWriter(os, { "service_id", "date", "exception_type" });
}

// ____________________________________________________________________________
bool Writer::writeCalendarDate(const gtfs::CalendarDateFlat& s,
    CsvWriter* csvw) const
{
    csvw->writeString(s.id);
    csvw->writeInt(s.date.getYYYYMMDD());
    csvw->writeInt(s.type);
    csvw->flushLine();

    return true;
}

// ____________________________________________________________________________
bool Writer::writeCalendarDates(gtfs::Feed* f, std::ostream* os) const
{
    auto csvw = getCalendarDatesCsvw(os);
    csvw.flushLine();

    for (const auto& r : f->getServices()) {
        for (const auto& e : r.second->getExceptions()) {
            gtfs::CalendarDateFlat cd;
            cd.date = e.first;
            cd.id = r.second->getId();
            cd.type = e.second;
            writeCalendarDate(cd, &csvw);
        }
    }

    return true;
}

// ____________________________________________________________________________
CsvWriter Writer::getFrequencyCsvw(std::ostream* os)
{
    return CsvWriter(
        os, { "trip_id", "start_time", "end_time", "headway_secs", "exact_times" });
}

// ____________________________________________________________________________
bool Writer::writeFrequency(const gtfs::Frequency::Flat& f, CsvWriter* csvw) const
{
    csvw->writeString(f.tripId);
    csvw->writeString(f.startTime.toString());
    csvw->writeString(f.endTime.toString());
    csvw->writeInt(f.headwaySecs);
    csvw->writeInt(f.exactTimes);
    csvw->flushLine();
    return true;
}

// ____________________________________________________________________________
bool Writer::writeFrequencies(gtfs::Feed* f, std::ostream* os) const
{
    auto csvw = getFrequencyCsvw(os);
    csvw.flushLine();

    for (const auto& t : f->getTrips()) {
        for (const auto& f : t.second->getFrequencies()) {
            writeFrequency(gtfs::Frequency::Flat{ t.second->getId(), f.getStartTime(), f.getEndTime(), f.getHeadwaySecs(), f.hasExactTimes() }, &csvw);
        }
    }

    return true;
}

// ___________________________________________________________________________
void Writer::cannotWrite(const std::string& file)
{
    throw exceptions::WriteException("Could not write to file.", file);
}
