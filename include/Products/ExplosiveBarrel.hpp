#pragma once
#include <Interfaces/Aliases.hpp>
#include <Interfaces/ProductFlags.hpp>
#include <PicoJson/picojson.h>
#include <Products/BasicProduct.hpp>
#include <memory>
#include <string>
#include <vector>

using ProductLabelFlags = warehouseInterface::ProductLabelFlags;

namespace warehouse {

    class ExplosiveBarrel : public BasicProduct {

    public:

        ExplosiveBarrel(const std::string &itemName, const float &itemSize) 
            : BasicProduct(itemName, itemSize) {

            objectGroup_ = "ExplosiveBarrel";

            using namespace magic_enum::bitwise_operators;
            itemFlags_ = (ProductLabelFlags::explosives | itemFlags_);
            itemFlags_ = (ProductLabelFlags::handleWithCare | itemFlags_);

        }

        std::string name() const {

            return BasicProduct::name();

        }

        float itemSize() const {

            return BasicProduct::itemSize();

        }

        ProductLabelFlags itemFlags() const {

            return BasicProduct::itemFlags();

        }

        picojson::object asJson() const {

            return BasicProduct::asJson();

        }

        warehouseInterface::ProductDescriptionJson serialize() const {

            return BasicProduct::serialize();

        }

    };

}