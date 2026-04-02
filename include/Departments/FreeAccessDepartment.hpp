#pragma once
#include <PicoJson/picojson.h>

#include <Interfaces/Aliases.hpp>
#include <Interfaces/IProduct.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Departments/BasicDepartment.hpp>

using BasicDepartment = warehouse::BasicDepartment;

namespace warehouse {

    class FreeAccessDepartment : public BasicDepartment {

        public:

            FreeAccessDepartment(const float& maxOccupancy) : BasicDepartment(maxOccupancy) {

                departmentName_ = "FreeAccessDepartment";

            }

            bool addItem(IProductPtr ptr) {

                return BasicDepartment::addItem(std::move(ptr));

            }

            IProductPtr getItem(const ProductDescriptionJson &desc) override {

                std::vector<IProductPtr>::iterator it = find_if(products_.begin(), products_.end(),
                    [&](IProductPtr& ptr){ 

                        if (ptr->serialize() == desc) {

                            return true;

                        }

                        picojson::value value;
                        picojson::parse(value, desc);
                        picojson::object given = value.get<picojson::object>();

                        picojson::value name = given["name"];
                        picojson::value clas = given["class"];
                        picojson::value nothing = value.get("NoThInG");

                        if (name != nothing) {

                            if (picojson::value(ptr->name()) == given["name"]) {

                                return true;

                            }

                        } else if (clas != nothing) {

                            if (ptr->asJson()["class"] == given["class"]) {

                                return true;

                            }

                        }

                        return false;

                    }
                );

                if (it == products_.end()) {

                    return nullptr;

                }

                IProductPtr ptr = std::move(*it);

                occupancy_ -= ptr->itemSize();
                products_.erase(std::remove(products_.begin(), products_.end(), *it));

                return ptr;

            }

            float getOccupancy() const {

                return BasicDepartment::getOccupancy();

            }

            float getMaxOccupancy() const {

                return BasicDepartment::getMaxOccupancy();

            }

            float getMaxItemSize() const {

                return BasicDepartment::getMaxItemSize();

            }

            ProductLabelFlags getSupportedFlags() const {

                return BasicDepartment::getSupportedFlags();

            }

            picojson::object asJson() const {

                return BasicDepartment::asJson();

            }

            DepartmentStateJson serialize() const {

                return BasicDepartment::serialize();

            }

            picojson::array serializedItems() const {

                return BasicDepartment::serializedItems();

            }

            std::string departmentName() const {

                return BasicDepartment::departmentName();

            }

    };

}