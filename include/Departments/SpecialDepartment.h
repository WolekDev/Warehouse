#pragma once

#include <Departments/LIFOAccessDepartment.hpp>

using LIFOAccessDepartment = warehouse::LIFOAccessDepartment;

namespace warehouse {

    class SpecialDepartment : public LIFOAccessDepartment {

        public:

            SpecialDepartment(const float& maxOccupancy);

            bool addItem(IProductPtr ptr);

            IProductPtr getItem(const ProductDescriptionJson &desc);

            float getOccupancy() const;

            float getMaxOccupancy() const;

            float getMaxItemSize() const;

            ProductLabelFlags getSupportedFlags() const;

            picojson::object asJson() const;

            DepartmentStateJson serialize() const;

            picojson::array serializedItems() const;

            std::string departmentName() const;

    };

}