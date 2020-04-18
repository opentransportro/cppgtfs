#include <cppgtfs/gtfs/Trip.h>

namespace cppgtfs::gtfs
{
    Trip::Trip(
        const std::string& id,
        Route::Ref r,
        Service::Ref s,
        const std::string& hs,
        const std::string& short_name,
        DIRECTION dir,
        const std::string& blockid,
        Shape::Ref shp,
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
    const std::string& Trip::getId() const
    {
        return _id;
    }

// _____________________________________________________________________________

    Route::Ref Trip::getRoute()
    {
        return _route;
    }

// _____________________________________________________________________________

    Route::Ref Trip::getRoute() const
    {
        return _route;
    }

// _____________________________________________________________________________

    Service::Ref Trip::getService()
    {
        return _service;
    }

// _____________________________________________________________________________

    Service::Ref Trip::getService() const
    {
        return _service;
    }

// _____________________________________________________________________________

    const std::string& Trip::getHeadsign()
    const
    {
        return _headsign;
    }

// _____________________________________________________________________________

    const std::string& Trip::getShortname() const
    {
        return _short_name;
    }

// _____________________________________________________________________________

    Trip::DIRECTION Trip::getDirection() const
    {
        return _dir;
    }

// _____________________________________________________________________________

    const std::string& Trip::getBlockId() const
    {
        return _block_id;
    }

// _____________________________________________________________________________

    Shape::Ref Trip::getShape()
    {
        return _shape;
    }

// _____________________________________________________________________________
    Shape::Ref Trip::getShape() const
    {
        return _shape;
    }

// _____________________________________________________________________________

    void Trip::setShape(Shape::Ref shp)
    {
        _shape = shp;
    }

// _____________________________________________________________________________

    Trip::WC_BIKE_ACCESSIBLE Trip::getWheelchairAccessibility() const
    {
        return _wc;
    }

// _____________________________________________________________________________

    Trip::WC_BIKE_ACCESSIBLE Trip::getBikesAllowed() const
    {
        return _ba;
    }

// _____________________________________________________________________________

    const typename Trip::StopTimes& Trip::getStopTimes() const
    {
        return _stoptimes;
    }

// _____________________________________________________________________________

    typename Trip::StopTimes& Trip::getStopTimes()
    {
        return _stoptimes;
    }

// _____________________________________________________________________________

    const typename Trip::Frequencies& Trip::getFrequencies() const
    {
        return _frequencies;
    }

// _____________________________________________________________________________

    Trip::Frequencies & Trip::getFrequencies()
    {
        return _frequencies;
    }

// _____________________________________________________________________________

    bool Trip::addStopTime(const StopTime& t)
    {
        for (size_t i = 0; i < _stoptimes.size(); i++) {
            if (_stoptimes[i].getSeq() == t.getSeq()) return false;
        }
        _stoptimes.reserve(_stoptimes.size() + 1);
        _stoptimes.push_back(t);
        auto cmp = StopTimeCompare();
        std::sort(_stoptimes.begin(), _stoptimes.end(), cmp);
        return true;
    }

// _____________________________________________________________________________

    void Trip::addFrequency(const Frequency& t)
    {
        _frequencies.push_back(t);
    }
}