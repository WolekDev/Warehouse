#include <Departments/SmallElectronicDepartment.h>

namespace warehouse {

    SmallElectronicDepartment::SmallElectronicDepartment(const float& maxOccupancy) : FreeAccessDepartment(maxOccupancy) {

        departmentName_ = "SmallElectronicDepartment";
        maxItemSize_ = 5.0f;
        supportedFlags_ = static_cast<ProductLabelFlags> (144);

    }

    bool SmallElectronicDepartment::addItem(IProductPtr ptr) {

        return FreeAccessDepartment::addItem(std::move(ptr));

    }

    IProductPtr SmallElectronicDepartment::getItem(const ProductDescriptionJson &desc) {

        return FreeAccessDepartment::getItem(desc);

    }

    float SmallElectronicDepartment::getOccupancy() const {

        return FreeAccessDepartment::getOccupancy();

    }

    float SmallElectronicDepartment::getMaxOccupancy() const {

        return FreeAccessDepartment::getMaxOccupancy();

    }

    float SmallElectronicDepartment::getMaxItemSize() const {

        return FreeAccessDepartment::getMaxItemSize();

    }

    ProductLabelFlags SmallElectronicDepartment::getSupportedFlags() const {

        return FreeAccessDepartment::getSupportedFlags();

    }

    picojson::object SmallElectronicDepartment::asJson() const {

        return FreeAccessDepartment::asJson();

    }

    DepartmentStateJson SmallElectronicDepartment::serialize() const {

        return FreeAccessDepartment::serialize();

    }

    picojson::array SmallElectronicDepartment::serializedItems() const {

        return FreeAccessDepartment::serializedItems();

    }

    std::string SmallElectronicDepartment::departmentName() const {

        return FreeAccessDepartment::departmentName();

    }

}