// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
TripB<StopTimeT, ServiceT, RouteT, ShapeT>::TripB(
    const std::string& id,
    typename RouteT::Ref r,
    typename ServiceT::Ref s,
    const std::string& hs,
    const std::string& short_name,
    DIRECTION dir,
    const std::string& blockid,
    typename ShapeT::Ref shp,
    WC_BIKE_ACCESSIBLE wc,
    WC_BIKE_ACCESSIBLE ba) :
    _id(id),
    _route(r),
    _service(s),
    _headsign(hs),
    _short_name(short_name),
    _dir(dir),
    _block_id(blockid),
    _shape(shp),
    _wc(wc),
    _ba(ba)
{}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const std::string& TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getId() const
{
    return _id;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename RouteT::Ref TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getRoute()
{
    return _route;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const typename RouteT::Ref
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getRoute() const
{
    return _route;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename ServiceT::Ref
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getService()
{
    return _service;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const typename ServiceT::Ref
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getService() const
{
    return _service;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const std::string& TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getHeadsign()
    const
{
    return _headsign;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const std::string& TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getShortname()
    const
{
    return _short_name;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename TripB<StopTimeT, ServiceT, RouteT, ShapeT>::DIRECTION
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getDirection() const
{
    return _dir;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const std::string& TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getBlockId()
    const
{
    return _block_id;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename ShapeT::Ref TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getShape()
{
    return _shape;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const typename ShapeT::Ref
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getShape() const
{
    return _shape;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
void TripB<StopTimeT, ServiceT, RouteT, ShapeT>::setShape(
    typename ShapeT::Ref shp)
{
    _shape = shp;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename TripB<StopTimeT, ServiceT, RouteT, ShapeT>::WC_BIKE_ACCESSIBLE
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getWheelchairAccessibility() const
{
    return _wc;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename TripB<StopTimeT, ServiceT, RouteT, ShapeT>::WC_BIKE_ACCESSIBLE
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getBikesAllowed() const
{
    return _ba;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const typename TripB<StopTimeT, ServiceT, RouteT, ShapeT>::StopTimes&
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getStopTimes() const
{
    return _stoptimes;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename TripB<StopTimeT, ServiceT, RouteT, ShapeT>::StopTimes&
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getStopTimes()
{
    return _stoptimes;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
const typename TripB<StopTimeT, ServiceT, RouteT, ShapeT>::Frequencies&
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getFrequencies() const
{
    return _frequencies;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
typename TripB<StopTimeT, ServiceT, RouteT, ShapeT>::Frequencies&
    TripB<StopTimeT, ServiceT, RouteT, ShapeT>::getFrequencies()
{
    return _frequencies;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
bool TripB<StopTimeT, ServiceT, RouteT, ShapeT>::addStopTime(
    const StopTimeT& t)
{
    for (size_t i = 0; i < _stoptimes.size(); i++) {
        if (_stoptimes[i].getSeq() == t.getSeq()) return false;
    }
    _stoptimes.reserve(_stoptimes.size() + 1);
    _stoptimes.push_back(t);
    auto cmp = StopTimeCompare<StopTimeT>();
    std::sort(_stoptimes.begin(), _stoptimes.end(), cmp);
    return true;
}

// _____________________________________________________________________________
template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
void TripB<StopTimeT, ServiceT, RouteT, ShapeT>::addFrequency(
    const Frequency& t)
{
    _frequencies.push_back(t);
}
