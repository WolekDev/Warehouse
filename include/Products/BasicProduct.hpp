#pragma once
#include <Interfaces/Aliases.hpp>
#include <Interfaces/ProductFlags.hpp>
#include <Interfaces/IProduct.hpp>
#include <PicoJson/picojson.h>
#include <MagicEnum/magic_enum.hpp>
#include <memory>
#include <string>
#include <vector>

using ProductLabelFlags = warehouseInterface::ProductLabelFlags;
using IProduct = warehouseInterface::IProduct;

namespace warehouse {

    class BasicProduct : public IProduct {

    protected:

        std::string itemName_;
        std::string objectGroup_ = "";
        ProductLabelFlags itemFlags_ = static_cast<ProductLabelFlags> (0);
        float itemSize_;

    public:

        explicit BasicProduct(const std::string &itemName, const float &itemSize) 
            : itemName_(itemName), itemSize_(itemSize) {}

        std::string name() const override {

            return this->itemName_;

        }

        float itemSize() const override {

            return this->itemSize_;

        }

        ProductLabelFlags itemFlags() const {

            return this->itemFlags_;

        }

        picojson::object asJson() const {

            picojson::object o;
            o["class"] = picojson::value(objectGroup_);
            o["name"] = picojson::value(itemName_);
            o["size"] = picojson::value(itemSize_);

            picojson::array arr;

            using namespace magic_enum::bitwise_operators;

            if ((ProductLabelFlags::fireHazardous & itemFlags_) == ProductLabelFlags::fireHazardous) {
                arr.push_back(picojson::value("fireHazardous"));
            }
            if ((ProductLabelFlags::explosives & itemFlags_) == ProductLabelFlags::explosives) {
                arr.push_back(picojson::value("explosives"));
            }
            if ((ProductLabelFlags::fragile & itemFlags_) == ProductLabelFlags::fragile) {
                arr.push_back(picojson::value("fragile"));
            }
            if ((ProductLabelFlags::upWard & itemFlags_) == ProductLabelFlags::upWard) {
                arr.push_back(picojson::value("upWard"));
            }
            if ((ProductLabelFlags::keepDry & itemFlags_) == ProductLabelFlags::keepDry) {
                arr.push_back(picojson::value("keepDry"));
            }
            if ((ProductLabelFlags::handleWithCare & itemFlags_) == ProductLabelFlags::handleWithCare) {
                arr.push_back(picojson::value("handleWithCare"));
            }
            if ((ProductLabelFlags::keepFrozen & itemFlags_) == ProductLabelFlags::keepFrozen) {
                arr.push_back(picojson::value("keepFrozen"));
            }
            if ((ProductLabelFlags::esdSensitive & itemFlags_) == ProductLabelFlags::esdSensitive) {
                arr.push_back(picojson::value("esdSensitive"));
            }

            o["flags"] = picojson::value(arr);

            return o;

        }

        warehouseInterface::ProductDescriptionJson serialize() const {

            picojson::value val = picojson::value(asJson());

            warehouseInterface::ProductDescriptionJson serialized = val.serialize();

            return serialized;

        }

    };

}