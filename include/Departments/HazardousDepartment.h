#pragma once

#include <Departments/FIFOAccessDepartment.hpp>

using FIFOAccessDepartment = warehouse::FIFOAccessDepartment;

namespace warehouse {

    class HazardousDepartment : public FIFOAccessDepartment {

        public:

            HazardousDepartment(const float& maxOccupancy);

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