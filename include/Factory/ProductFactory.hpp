#pragma once
#include <Interfaces/IProduct.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>
#include <Products/ProductsList.hpp>

namespace warehouse
{
class ProductFactory
{

    public:

        warehouseInterface::IProductPtr createProduct(const std::string &className, 
                                        const std::string &name, const float size) const {

            warehouseInterface::IProductPtr product;

            if (className == "AcetoneBarrel") {

                product = static_cast<warehouseInterface::IProductPtr> (new AcetoneBarrel(name, size));

            } else if (className == "AstronautsIceCream") {

                product = static_cast<warehouseInterface::IProductPtr> (new AstronautsIceCream(name, size));

            } else if (className == "ElectronicParts") {

                product = static_cast<warehouseInterface::IProductPtr> (new ElectronicParts(name, size));

            } else if (className == "ExplosiveBarrel") {

                product = static_cast<warehouseInterface::IProductPtr> (new ExplosiveBarrel(name, size));

            } else if (className == "GlassWare") {

                product = static_cast<warehouseInterface::IProductPtr> (new GlassWare(name, size));

            } else if (className == "IndustrialServerRack") {

                product = static_cast<warehouseInterface::IProductPtr> (new IndustrialServerRack(name, size));

            } else if (className == "TV") { 

                product = static_cast<warehouseInterface::IProductPtr> (new TV(name, size));

            } else {

                throw std::runtime_error("nope");

            }

            return product;

        }

};

}  // namespace warehouse