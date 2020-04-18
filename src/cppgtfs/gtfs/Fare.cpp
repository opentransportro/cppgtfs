#include <cppgtfs/gtfs/Fare.h>

namespace cppgtfs::gtfs
{
    FareRule::Fields cppgtfs::gtfs::FareRule::Fields::fromCsvParser(const csv::CsvParser& csvp)

    {
        FareRule::Fields f;
        f.fareIdFld = csvp.getFieldIndex("fare_id");
        f.routeIdFld = csvp.getOptFieldIndex("route_id");
        f.originIdFld = csvp.getOptFieldIndex("origin_id");
        f.destinationIdFld = csvp.getOptFieldIndex("destination_id");
        f.containsIdFld = csvp.getOptFieldIndex("contains_id");
        return f;
    }
    Fare::Fields cppgtfs::gtfs::Fare::Fields::fromCsvParser(const csv::CsvParser& csvp)
    {
        Fare::Fields f;
        f.fareIdFld = csvp.getFieldIndex("fare_id");
        f.priceFld = csvp.getFieldIndex("price");
        f.currencyTypeFld = csvp.getFieldIndex("currency_type");
        f.paymentMethodFld = csvp.getFieldIndex("payment_method");
        f.transfersFld = csvp.getFieldIndex("transfers");
        f.agencyFld = csvp.getOptFieldIndex("agency");
        f.transferDurationFld = csvp.getOptFieldIndex("transfer_duration");
        return f;
    }
    FareRule::FareRule(Route::Ref route, std::string originId, std::string destId, std::string containsId) :
        _route(route),
        _originId(std::move(originId)),
        _destId(std::move(destId)),
        _containsId(std::move(containsId)) {}
    Route::Ref FareRule::getRoute() const { return _route; }
    const std::string& FareRule::getOriginId() const { return _originId; }
    const std::string& FareRule::getDestId() const { return _destId; }
    const std::string& FareRule::getContainsId() const { return _containsId; }
    Fare::Fare(std::string id, double price, std::string currencyType, Fare::PAYMENT_METHOD paymentMethod, Fare::NUM_TRANSFERS numTransfers, Agency* agency, int64_t dur) :
        _id(std::move(id)),
        _price(price),
        _currencyType(std::move(currencyType)),
        _paymentMethod(paymentMethod),
        _numTransfers(numTransfers),
        _agency(agency),
        _duration(dur) {}
    const std::string& Fare::getId() const { return _id; }
    double Fare::getPrice() const { return _price; }
    const std::string& Fare::getCurrencyType() const { return _currencyType; }
    Fare::PAYMENT_METHOD Fare::getPaymentMethod() const { return _paymentMethod; }
    Fare::NUM_TRANSFERS Fare::getNumTransfers() const { return _numTransfers; }
    Agency* Fare::getAgency() const { return _agency; }
    int64_t Fare::getDuration() const { return _duration; }
    const std::vector<FareRule>& Fare::getFareRules() const
    {
        return _fareRules;
    }
    void Fare::addFareRule(const FareRule& rule) { _fareRules.push_back(rule); }
    Fare::Flat Fare::getFlat() const
    {
        return { _id, _price, _currencyType, _paymentMethod, _numTransfers, _agency != nullptr ? _agency->getId() : "", _duration };
    }
    void Fare::setId(const std::string& id)
    {
        _id = id;
    }
    void Fare::setPrice(double price)
    {
        _price = price;
    }
    void Fare::setCurrencyType(const std::string& currencyType)
    {
        _currencyType = currencyType;
    }
    void Fare::setPaymentMethod(Fare::PAYMENT_METHOD paymentMethod)
    {
        _paymentMethod = paymentMethod;
    }
    void Fare::setNumTransfers(Fare::NUM_TRANSFERS numTransfers)
    {
        _numTransfers = numTransfers;
    }
    void Fare::setAgency(Agency* agency)
    {
        _agency = agency;
    }
    void Fare::setDuration(int64_t duration)
    {
        _duration = duration;
    }
}    // namespace cppgtfs::gtfs
