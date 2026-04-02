#include <Departments/OverSizeElectronicDepartment.h>

namespace warehouse {

    OverSizeElectronicDepartment::OverSizeElectronicDepartment(const float& maxOccupancy) : FreeAccessDepartment(maxOccupancy) {

        departmentName_ = "OverSizeElectronicDepartment";
        supportedFlags_ = static_cast<ProductLabelFlags> (144);

    }

    bool OverSizeElectronicDepartment::addItem(IProductPtr ptr) {

        return FreeAccessDepartment::addItem(std::move(ptr));

    }

    IProductPtr OverSizeElectronicDepartment::getItem(const ProductDescriptionJson &desc) {

        return FreeAccessDepartment::getItem(desc);

    }

    float OverSizeElectronicDepartment::getOccupancy() const {

        return FreeAccessDepartment::getOccupancy();

    }

    float OverSizeElectronicDepartment::getMaxOccupancy() const {

        return FreeAccessDepartment::getMaxOccupancy();

    }

    float OverSizeElectronicDepartment::getMaxItemSize() const {

        return FreeAccessDepartment::getMaxItemSize();

    }

    picojson::object OverSizeElectronicDepartment::asJson() const {

        return FreeAccessDepartment::asJson();

    }

    DepartmentStateJson OverSizeElectronicDepartment::serialize() const {

        return FreeAccessDepartment::serialize();

    }

    picojson::array OverSizeElectronicDepartment::serializedItems() const {

        return FreeAccessDepartment::serializedItems();

    }

    std::string OverSizeElectronicDepartment::departmentName() const {

        return FreeAccessDepartment::departmentName();

    }

}