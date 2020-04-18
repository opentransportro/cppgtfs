#include <cppgtfs/gtfs/Trip.h>

namespace cppgtfs::gtfs
{
    Trip::Trip(const std::string& id, Route::Ref r, Service::Ref s, const std::string& hs, const std::string& short_name, DIRECTION dir,
        const std::string& blockid, Shape::Ref shp, WC_BIKE_ACCESSIBLE wc, WC_BIKE_ACCESSIBLE ba) :
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


    const std::string& Trip::getId() const
    {
        return _id;
    }



    Route::Ref Trip::getRoute()
    {
        return _route;
    }



    Route::Ref Trip::getRoute() const
    {
        return _route;
    }



    Service::Ref Trip::getService()
    {
        return _service;
    }



    Service::Ref Trip::getService() const
    {
        return _service;
    }



    const std::string& Trip::getHeadsign()
    const
    {
        return _headsign;
    }



    const std::string& Trip::getShortname() const
    {
        return _short_name;
    }



    Trip::DIRECTION Trip::getDirection() const
    {
        return _dir;
    }



    const std::string& Trip::getBlockId() const
    {
        return _block_id;
    }



    Shape::Ref Trip::getShape()
    {
        return _shape;
    }


    Shape::Ref Trip::getShape() const
    {
        return _shape;
    }



    void Trip::setShape(Shape::Ref shp)
    {
        _shape = shp;
    }



    Trip::WC_BIKE_ACCESSIBLE Trip::getWheelchairAccessibility() const
    {
        return _wc;
    }



    Trip::WC_BIKE_ACCESSIBLE Trip::getBikesAllowed() const
    {
        return _ba;
    }



    const typename Trip::StopTimes& Trip::getStopTimes() const
    {
        return _stoptimes;
    }



    typename Trip::StopTimes& Trip::getStopTimes()
    {
        return _stoptimes;
    }



    const typename Trip::Frequencies& Trip::getFrequencies() const
    {
        return _frequencies;
    }



    Trip::Frequencies & Trip::getFrequencies()
    {
        return _frequencies;
    }



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



    void Trip::addFrequency(const Frequency& t)
    {
        _frequencies.push_back(t);
    }
    gtfs::TripFlat Trip::getFlat() const
    {
        return gtfs::TripFlat{
                _id,
                _route->getId(),
                _service->getId(),
                _headsign,
                _short_name,
                _dir,
                _block_id,
                _shape->getId(),
                _wc,
                _ba
        };
    }
}