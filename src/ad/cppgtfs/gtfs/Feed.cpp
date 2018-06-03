// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#include <string>
#include <unordered_map>
#include <utility>
#include "Feed.h"

using ad::cppgtfs::gtfs::Feed;
using ad::cppgtfs::gtfs::Agencies;
using ad::cppgtfs::gtfs::Stops;
using ad::cppgtfs::gtfs::Trips;
using ad::cppgtfs::gtfs::Routes;
using ad::cppgtfs::gtfs::Shapes;
using ad::cppgtfs::gtfs::Services;
using ad::cppgtfs::gtfs::ServiceDate;

// ____________________________________________________________________________
const Agencies& Feed::getAgencies() const { return _agencies; }

// ____________________________________________________________________________
Agencies& Feed::getAgencies() { return _agencies; }

// ____________________________________________________________________________
const Stops& Feed::getStops() const { return _stops; }

// ____________________________________________________________________________
Stops& Feed::getStops() { return _stops; }

// ____________________________________________________________________________
const Routes& Feed::getRoutes() const { return _routes; }

// ____________________________________________________________________________
Routes& Feed::getRoutes() { return _routes; }

// ____________________________________________________________________________
const Trips& Feed::getTrips() const { return _trips; }

// ____________________________________________________________________________
Trips& Feed::getTrips() { return _trips; }

// ____________________________________________________________________________
const Shapes& Feed::getShapes() const { return _shapes; }

// ____________________________________________________________________________
Shapes& Feed::getShapes() { return _shapes; }

// ____________________________________________________________________________
const Services& Feed::getServices() const { return _services; }

// ____________________________________________________________________________
Services& Feed::getServices() { return _services; }

// ____________________________________________________________________________
const std::string& Feed::getPublisherName() const { return _publisherName; }
// ____________________________________________________________________________
const std::string& Feed::getPublisherUrl() const { return _publisherName; }
// ____________________________________________________________________________
const std::string& Feed::getLang() const { return _lang; }
// ____________________________________________________________________________
const std::string& Feed::getVersion() const { return _version; }
// ____________________________________________________________________________
const ServiceDate& Feed::getStartDate() const { return _startDate; }

// ____________________________________________________________________________
const ServiceDate& Feed::getEndDate() const { return _endDate; }

// ____________________________________________________________________________
void Feed::setPublisherName(const std::string& name) { _publisherName = name;}
// ____________________________________________________________________________
void Feed::setPublisherUrl(const std::string& url) { _publisherUrl = url;}
// ____________________________________________________________________________
void Feed::setLang(const std::string& lang) { _lang = lang; }
// ____________________________________________________________________________
void Feed::setVersion(const std::string& version) { _version = version;}
// ____________________________________________________________________________
void Feed::setStartDate(const ServiceDate& start) { _startDate = start; }
// ____________________________________________________________________________
void Feed::setEndDate(const ServiceDate& end) { _endDate = end; }

// ____________________________________________________________________________
void Feed::updateBox(double lat, double lon) {
  if (lat > _maxLat) _maxLat = lat;
  if (lon > _maxLon) _maxLon = lon;
  if (lat < _minLat) _minLat = lat;
  if (lon < _minLon) _minLon = lon;
}

// ____________________________________________________________________________
double Feed::getMinLat() const { return _minLat; }

// ____________________________________________________________________________
double Feed::getMinLon() const { return _minLon; }

// ____________________________________________________________________________
double Feed::getMaxLat() const { return _maxLat; }

// ____________________________________________________________________________
double Feed::getMaxLon() const { return _maxLon; }
