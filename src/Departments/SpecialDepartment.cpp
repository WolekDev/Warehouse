#include <Departments/SpecialDepartment.h>

namespace warehouse {

    SpecialDepartment::SpecialDepartment(const float& maxOccupancy) : LIFOAccessDepartment(maxOccupancy) {

        departmentName_ = "SpecialDepartment";
        supportedFlags_ = static_cast<ProductLabelFlags> (60);

    }

    bool SpecialDepartment::addItem(IProductPtr ptr) {

        return LIFOAccessDepartment::addItem(std::move(ptr));

    }

    IProductPtr SpecialDepartment::getItem(const ProductDescriptionJson &desc) {

        return LIFOAccessDepartment::getItem(desc);

    }

    float SpecialDepartment::getOccupancy() const {

        return LIFOAccessDepartment::getOccupancy();

    }

    float SpecialDepartment::getMaxOccupancy() const {

        return LIFOAccessDepartment::getMaxOccupancy();

    }

    float SpecialDepartment::getMaxItemSize() const {

        return LIFOAccessDepartment::getMaxItemSize();

    }

    ProductLabelFlags SpecialDepartment::getSupportedFlags() const {

        return LIFOAccessDepartment::getSupportedFlags();

    }

    picojson::object SpecialDepartment::asJson() const {

        return LIFOAccessDepartment::asJson();

    }

    DepartmentStateJson SpecialDepartment::serialize() const {

        return LIFOAccessDepartment::serialize();

    }

    picojson::array SpecialDepartment::serializedItems() const {

        return LIFOAccessDepartment::serializedItems();

    }

    std::string SpecialDepartment::departmentName() const {

        return LIFOAccessDepartment::departmentName();

    }

}