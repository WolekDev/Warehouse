#pragma once

#include <Departments/FreeAccessDepartment.hpp>

using FreeAccessDepartment = warehouse::FreeAccessDepartment;

namespace warehouse {

    class OverSizeElectronicDepartment : public FreeAccessDepartment {

        public:

            OverSizeElectronicDepartment(const float& maxOccupancy);

            bool addItem(IProductPtr ptr);

            IProductPtr getItem(const ProductDescriptionJson &desc);

            float getOccupancy() const;

            float getMaxOccupancy() const;

            float getMaxItemSize() const;

            picojson::object asJson() const;

            DepartmentStateJson serialize() const;

            picojson::array serializedItems() const;

            std::string departmentName() const;

    };

}