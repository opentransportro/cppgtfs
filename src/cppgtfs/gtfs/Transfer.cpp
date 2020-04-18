#include <cppgtfs/gtfs/Transfer.h>

namespace cppgtfs::gtfs
{
    TransfersFields TransfersFields::fromCsvParser(const csv::CsvParser& csvp)
    {
        cppgtfs::gtfs::TransfersFields t;
        t.fromStopIdFld = csvp.getFieldIndex("from_stop_id");
        t.toStopIdFld = csvp.getFieldIndex("to_stop_id");
        t.transferTypeFld = csvp.getFieldIndex("transfer_type");
        t.minTransferTimeFld = csvp.getOptFieldIndex("min_transfer_time");
        return t;
    }
    Transfer::Transfer(Stop* fromStop, Stop* toStop, Transfer::TYPE type, int32_t tTime) :
        _fromStop(fromStop), _toStop(toStop), _type(type), _tTime(tTime) {}
    Stop* Transfer::getFromStop() const { return _fromStop; }
    Stop* Transfer::getToStop() const { return _toStop; }
    Transfer::TYPE Transfer::getType() const { return _type; }
    int32_t Transfer::getMinTransferTime() const { return _tTime; }
    gtfs::TransferFlat Transfer::getFlat() const
    {
        return gtfs::TransferFlat{ getFromStop()->getId(), getToStop()->getId(), getType(), getMinTransferTime() };
    }
    void Transfer::setFromStop(Stop* fromStop)
    {
        _fromStop = fromStop;
    }
    void Transfer::setToStop(Stop* toStop)
    {
        _toStop = toStop;
    }
    void Transfer::setType(Transfer::TYPE type)
    {
        _type = type;
    }
    void Transfer::setTTime(int32_t tTime)
    {
        _tTime = tTime;
    }
}    // namespace cppgtfs::gtfs