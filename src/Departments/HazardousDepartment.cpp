#include <Departments/HazardousDepartment.h>

namespace warehouse {

    HazardousDepartment::HazardousDepartment(const float& maxOccupancy) : FIFOAccessDepartment(maxOccupancy) {

        departmentName_ = "HazardousDepartment";
        supportedFlags_ = static_cast<ProductLabelFlags> (19);

    }

    bool HazardousDepartment::addItem(IProductPtr ptr) {

        return FIFOAccessDepartment::addItem(std::move(ptr));

    }

    IProductPtr HazardousDepartment::getItem(const ProductDescriptionJson &desc) {

        return FIFOAccessDepartment::getItem(desc);

    }

    float HazardousDepartment::getOccupancy() const {

        return FIFOAccessDepartment::getOccupancy();

    }

    float HazardousDepartment::getMaxOccupancy() const {

        return FIFOAccessDepartment::getMaxOccupancy();

    }

    float HazardousDepartment::getMaxItemSize() const {

        return FIFOAccessDepartment::getMaxItemSize();

    }

    ProductLabelFlags HazardousDepartment::getSupportedFlags() const {

        return FIFOAccessDepartment::getSupportedFlags();

    }

    picojson::object HazardousDepartment::asJson() const {

        return FIFOAccessDepartment::asJson();

    }

    DepartmentStateJson HazardousDepartment::serialize() const {

        return FIFOAccessDepartment::serialize();

    }

    picojson::array HazardousDepartment::serializedItems() const {

        return FIFOAccessDepartment::serializedItems();

    }

    std::string HazardousDepartment::departmentName() const {

        return FIFOAccessDepartment::departmentName();

    }

}