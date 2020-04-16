//
// Created by vlad on 13.04.2020.
//

#include "CsvField.h"

using namespace ad::util;
CsvField::CsvField(const std::string& name, std::any value) :
    _name(name),
    _value(std::move(value))
{}
bool CsvField::has_value() const noexcept
{
    return _value.has_value();
}
int CsvField::toInt() const noexcept
{
    return toType<int>();
}
double CsvField::toDouble() const noexcept
{
    return toType<double>();
}
bool CsvField::toBool() const noexcept
{
    return toType<bool>();
}
std::string CsvField::toString() const noexcept
{
    auto str = toType<std::string>();
    if(str.empty()) {
        const auto *ptr = toType<const char*>();
        str = ptr != nullptr ? ptr: "";
    }
    return str;
}
