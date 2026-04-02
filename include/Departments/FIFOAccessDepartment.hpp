#pragma once
#include <PicoJson/picojson.h>

#include <Interfaces/Aliases.hpp>
#include <Interfaces/IProduct.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Departments/BasicDepartment.hpp>

using BasicDepartment = warehouse::BasicDepartment;

namespace warehouse {

    class FIFOAccessDepartment : public BasicDepartment {

        public:

            FIFOAccessDepartment(const float& maxOccupancy) : BasicDepartment(maxOccupancy) {

                departmentName_ = "FIFOAccessDepartment";

            }

            bool addItem(IProductPtr ptr) {

                return BasicDepartment::addItem(std::move(ptr));

            }

            IProductPtr getItem(const ProductDescriptionJson &desc) override {

                std::vector<IProductPtr>::iterator it = products_.begin();

                std::string serialized = (*it)->serialize();

                if (serialized == desc) {

                    IProductPtr output = std::move(*it);
                    occupancy_ -= output->itemSize();
                    products_.erase(std::remove(products_.begin(), products_.end(), *it));
                    return output;

                } else {

                    picojson::object obj = it->get()->asJson();
                    
                    picojson::value value;
                    picojson::parse(value, desc);
                    picojson::object given = value.get<picojson::object>();

                    picojson::value nothing = obj["NoThInG"];

                    if (given["name"] != nothing) {

                        if (obj["name"] == given["name"]) {

                            IProductPtr output = std::move(*it);
                            occupancy_ -= output->itemSize();
                            products_.erase(std::remove(products_.begin(), products_.end(), *it));
                            return output;

                        }

                    } else if (given["class"] != nothing) {

                        if (obj["class"] == given["class"]) {

                            IProductPtr output = std::move(*it);
                            occupancy_ -= output->itemSize();
                            products_.erase(std::remove(products_.begin(), products_.end(), *it));
                            return output;

                        }

                    }


                }

                return nullptr;

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