#ifndef CPPGTFS_CSVFIELD_H
#define CPPGTFS_CSVFIELD_H

#include <any>
#include <string>
#include <type_traits>

namespace csv
{
    class CsvField
    {
    public:
        explicit CsvField(const std::string& name, std::any value);

        ~CsvField() noexcept = default;

        [[nodiscard]] bool has_value() const noexcept;

        /**
         * Converts the value stored for the current field
         * @tparam T - desired return type
         * @param success - if operation was performed successfully or not
         * @return T
         */
        template<typename T>
        [[nodiscard]] T toType(bool* success = nullptr) const noexcept
        {
            try {
                if (has_value()) {
                    if (success != nullptr) { *success = true; }
                    return std::any_cast<T>(_value);
                }
            } catch (std::bad_any_cast& e) {
            }

            if (success != nullptr) { *success = false; }

            if (std::is_pointer<T>::value) {
                return 0;
            }
            return T{};
        }

        [[nodiscard]] int toInt() const noexcept;

        [[nodiscard]] double toDouble() const noexcept;

        [[nodiscard]] bool toBool() const noexcept;

        [[nodiscard]] std::string toString() const noexcept;

    private:
        const std::string& _name{};
        std::any _value{};
    };
}    // namespace csv


#endif    //CPPGTFS_CSVFIELD_H
