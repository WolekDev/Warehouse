#pragma once
#include <PicoJson/picojson.h>

#include <Interfaces/Aliases.hpp>
#include <Interfaces/IProduct.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Interfaces/IDepartment.hpp>
#include <vector>

using ProductLabelFlags = warehouseInterface::ProductLabelFlags;
using IDepartment = warehouseInterface::IDepartment;
using IProductPtr = warehouseInterface::IProductPtr;
using ProductDescriptionJson = warehouseInterface::ProductDescriptionJson;
using DepartmentStateJson = warehouseInterface::DepartmentStateJson;

namespace warehouse {

    class BasicDepartment : public IDepartment {

        protected:

            std::string departmentName_ = "";
            ProductLabelFlags supportedFlags_ = static_cast<ProductLabelFlags> (0);
            std::vector<IProductPtr> products_ = {};

        public:

            BasicDepartment(const float& maxOccupancy) {

                maxOccupancy_ = maxOccupancy;
                maxItemSize_ = std::numeric_limits<float>().max();

            }

            bool addItem(IProductPtr ptr) override {

                using namespace magic_enum::bitwise_operators;
                ProductLabelFlags flags = ptr->itemFlags();
                ProductLabelFlags notSupportedFlags = ~supportedFlags_;

                if ((flags | notSupportedFlags) == notSupportedFlags) {

                    return false;

                }

                if (ptr->itemSize() > maxItemSize_) {

                    return false;
                    
                }

                if (occupancy_ + ptr->itemSize() > maxOccupancy_) {

                    return false;

                }

                occupancy_ += ptr->itemSize();
                products_.push_back(std::move(ptr));
                
                return true;

            }

            virtual IProductPtr getItem(const ProductDescriptionJson &) = 0;

            float getOccupancy() const override {

                return IDepartment::occupancy_;

            }

            float getMaxOccupancy() const override {

                return IDepartment::maxOccupancy_;

            }

            float getMaxItemSize() const override {

                return IDepartment::maxItemSize_;

            }

            ProductLabelFlags getSupportedFlags() const override {

                return supportedFlags_;

            }

            picojson::object asJson() const override {

                picojson::object o;
                picojson::array arr = serializedItems();

                o["class"] = picojson::value(departmentName_);
                o["items"] = picojson::value(arr);
                o["maxOccupancy"] = picojson::value(maxOccupancy_);
                o["occupancy"] = picojson::value(occupancy_);

                return o;

            }

            DepartmentStateJson serialize() const override {

                picojson::value val = picojson::value(asJson());

                DepartmentStateJson serialized = val.serialize();

                return serialized;

            }

            picojson::array serializedItems() const override {

                picojson::array arr;

                for (size_t index = 0; index < products_.size(); index++) {

                    picojson::object o = products_.at(index)->asJson();
                    arr.push_back(picojson::value(o));

                }

                return arr;

            }

            std::string departmentName() const override {

                return departmentName_;

            }

    };

}