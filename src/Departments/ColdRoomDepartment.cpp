#include <Departments/ColdRoomDepartment.h>

namespace warehouse {

    ColdRoomDepartment::ColdRoomDepartment(const float& maxOccupancy) : FreeAccessDepartment(maxOccupancy) {

        departmentName_ = "ColdRoomDepartment";
        supportedFlags_ = static_cast<ProductLabelFlags> (80);

    }

    bool ColdRoomDepartment::addItem(IProductPtr ptr) {

        return FreeAccessDepartment::addItem(std::move(ptr));

    }

    IProductPtr ColdRoomDepartment::getItem(const ProductDescriptionJson &desc) {

        return FreeAccessDepartment::getItem(desc);

    }

    float ColdRoomDepartment::getOccupancy() const {

        return FreeAccessDepartment::getOccupancy();

    }

    float ColdRoomDepartment::getMaxOccupancy() const {

        return FreeAccessDepartment::getMaxOccupancy();

    }

    float ColdRoomDepartment::getMaxItemSize() const {

        return FreeAccessDepartment::getMaxItemSize();

    }

    ProductLabelFlags ColdRoomDepartment::getSupportedFlags() const {

        return FreeAccessDepartment::getSupportedFlags();

    }

    picojson::object ColdRoomDepartment::asJson() const {

        return FreeAccessDepartment::asJson();

    }

    DepartmentStateJson ColdRoomDepartment::serialize() const {

        return FreeAccessDepartment::serialize();

    }

    picojson::array ColdRoomDepartment::serializedItems() const {

        return FreeAccessDepartment::serializedItems();

    }

    std::string ColdRoomDepartment::departmentName() const {

        return FreeAccessDepartment::departmentName();

    }

}