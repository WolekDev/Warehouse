#include <Warehouse/Warehouse.h>

using ProductLabelFlags = warehouseInterface::ProductLabelFlags;
using IDepartmentPtr = warehouseInterface::IDepartmentPtr;
using IProductPtr = warehouseInterface::IProductPtr;
using DeliveryReportJson = warehouseInterface::DeliveryReportJson;
using WarehouseStateJson = warehouseInterface::WarehouseStateJson;
using IWarehouse = warehouseInterface::IWarehouse;
using Order = warehouseInterface::Order;
using OrderJson = warehouseInterface::OrderJson;

namespace warehouse {

    void Warehouse::addDepartment(IDepartmentPtr ptr) {

        departments_.push_back(std::move(ptr));

    }

    DeliveryReportJson Warehouse::newDelivery(std::vector<IProductPtr> productList) {

        using namespace magic_enum::bitwise_operators;

        if (productList.empty()) {

            return "{\"deliveryReport\":[{\"assignedDepartment\":\"None\",\"errorLog\":\"No products given.\",\"productName\":\"None\",\"status\":\"Fail\"}";

        }

        picojson::object report;
        picojson::array products;

        for (auto prod_it = productList.begin(); prod_it != productList.end(); ++prod_it) {

            picojson::object product;

            ProductLabelFlags product_flags = (*prod_it)->itemFlags();
            std::string optimal_department;

            std::string product_name = (*prod_it)->name();

            // Hazardous Department
            if (((product_flags | ProductLabelFlags::explosives) == product_flags) || 
                ((product_flags | ProductLabelFlags::fireHazardous) == product_flags)) {

                optimal_department = "HazardousDepartment";

                // End: Hazardous Department

            } else if ((product_flags | ProductLabelFlags::esdSensitive) == product_flags) {

                // Small Electronics Department
                if ((*prod_it)->itemSize() <= 5.0) {

                    optimal_department = "SmallElectronicDepartment";

                // Oversize Electronics Department
                } else {

                    optimal_department = "OverSizeElectronicDepartment";

                }

            // Cold Department
            } else if ((product_flags | ProductLabelFlags::keepFrozen) == product_flags) {

                optimal_department = "ColdRoomDepartment";

            // Special Department
            } else if (((product_flags | ProductLabelFlags::fragile) == product_flags) ||
                        ((product_flags | ProductLabelFlags::handleWithCare) == product_flags) ||
                        ((product_flags | ProductLabelFlags::upWard) == product_flags)) {

                optimal_department = "SpecialDepartment";

            // Any Department
            } else {

                optimal_department = "ANY";
            
            }

            if (optimal_department == "ANY") {

                bool anyHasSpace = false;
                bool productMoved = false;

                for (auto dep_it = departments_.begin(); dep_it != departments_.end(); ++dep_it) {

                    bool hasSpace = false;
                    bool correctFlags = false;

                    float itemSize = (*prod_it)->itemSize();
                    float depMaxOcc = (*dep_it)->getMaxOccupancy();
                    float depOcc = (*dep_it)->getOccupancy();

                    ProductLabelFlags depFlags = (*dep_it)->getSupportedFlags();

                    if (depOcc + itemSize <= depMaxOcc) {

                        hasSpace = true;
                        anyHasSpace = true;

                    }

                    if (((~depFlags) | product_flags) != (~depFlags)) {

                        correctFlags = true;

                    }

                    if (!(hasSpace && correctFlags)) {

                        continue;

                    }

                    (*dep_it)->addItem(std::move((*prod_it)));
                    productMoved = true;
                    optimal_department = (*dep_it)->departmentName();
                    break;

                }

                if (productMoved) {

                    product["assignedDepartment"] = picojson::value(optimal_department);
                    product["errorLog"]           = picojson::value("");
                    product["productName"]        = picojson::value(product_name);
                    product["status"]             = picojson::value("Success");
                    products.push_back(picojson::value(product));
                    continue;

                } else if (anyHasSpace) {

                    product["assignedDepartment"] = picojson::value("None");
                    product["errorLog"]           = picojson::value("Warehouse cannot store this product. Lack of required department.");
                    product["productName"]        = picojson::value(product_name);
                    product["status"]             = picojson::value("Fail");
                    products.push_back(picojson::value(product));
                    continue;

                } else {

                    product["assignedDepartment"] = picojson::value("None");
                    product["errorLog"]           = picojson::value("Warehouse cannot store this product. Lack of space in departments.");
                    product["productName"]        = picojson::value(product_name);
                    product["status"]             = picojson::value("Fail");
                    products.push_back(picojson::value(product));
                    continue;

                }

            // Specific Department needed
            } else {

                bool depFound = false;
                bool depHadSpace = false;

                for (auto dep_it = departments_.begin(); dep_it != departments_.end(); ++dep_it) {

                    if ((*dep_it)->departmentName() == optimal_department) {

                        depFound = true;

                        float itemSize = (*prod_it)->itemSize();
                        float depMaxOcc = (*dep_it)->getMaxOccupancy();
                        float depOcc = (*dep_it)->getOccupancy();

                        if (depOcc + itemSize <= depMaxOcc) {

                            depHadSpace = true;
                            (*dep_it)->addItem(std::move((*prod_it)));
                            break;

                        }

                    }

                }

                if (!depFound) {

                    product["assignedDepartment"] = picojson::value("None");
                    product["errorLog"]           = picojson::value("Warehouse cannot store this product. Lack of required department.");
                    product["productName"]        = picojson::value(product_name);
                    product["status"]             = picojson::value("Fail");
                    products.push_back(picojson::value(product));
                    continue;

                } else if (!depHadSpace) {

                    product["assignedDepartment"] = picojson::value("None");
                    product["errorLog"]           = picojson::value("Warehouse cannot store this product. Lack of space in departments.");
                    product["productName"]        = picojson::value(product_name);
                    product["status"]             = picojson::value("Fail");
                    products.push_back(picojson::value(product));
                    continue;

                } else {

                    product["assignedDepartment"] = picojson::value(optimal_department);
                    product["errorLog"]           = picojson::value("");
                    product["productName"]        = picojson::value(product_name);
                    product["status"]             = picojson::value("Success");
                    products.push_back(picojson::value(product));
                    continue;

                }

            }
                

        }

        report["deliveryReport"] = picojson::value(products);
        return picojson::value(report).serialize();

    }

    Order Warehouse::newOrder(const OrderJson &order) {

        picojson::value value;
        picojson::parse(value, order);
        picojson::object obj = value.get<picojson::object>();
        Order o{};
        o.receipt = order;

        if (!obj["order"].is<picojson::array>()) return o;

        picojson::array items = obj["order"].get<picojson::array>();

        std::vector<IProductPtr> products;

        for (auto item : items) {

            for (size_t dep_index = 0; dep_index < departments_.size(); dep_index++) {

                IProductPtr ptr = departments_.at(dep_index)->getItem(item.serialize());

                if (ptr != nullptr) {

                    products.push_back(std::move(ptr));
                    break;

                }

            }

        }

        o.products = std::move(products);
        return o;

    }

    OccupancyReportJson Warehouse::getOccupancyReport() const {

        picojson::object report;
        picojson::array departments;

        for (size_t i = 0; i < departments_.size(); i++) {

            picojson::object obj;
            std::string name = departments_.at(i)->departmentName();
            float occupancy = departments_.at(i)->getOccupancy();
            float maxOccupancy = departments_.at(i)->getMaxOccupancy();
            obj["departmentName"] = picojson::value(name);
            obj["maxOccupancy"] = picojson::value(maxOccupancy);
            obj["occupancy"] = picojson::value(occupancy);

            departments.push_back(picojson::value(obj));

        }

        report["departmentsOccupancy"] = picojson::value(departments);

        return picojson::value(report).serialize();

    }

    WarehouseStateJson Warehouse::saveWarehouseState() const {

        picojson::object warehouseState;
        picojson::array dep;

        for(size_t i = 0; i < departments_.size(); i++) {

            dep.push_back(picojson::value(departments_.at(i)->asJson()));

        }

        warehouseState["warehouseState"] = picojson::value(dep);
        return picojson::value(warehouseState).serialize();

    }

    bool Warehouse::loadWarehouseState(const WarehouseStateJson &state) {

        picojson::value val;
        picojson::parse(val, state);
        picojson::object obj = val.get<picojson::object>();

        if (!obj["warehouseState"].is<picojson::array>()) return false;

        picojson::array deps = obj["warehouseState"].get<picojson::array>();

        for (auto dep : deps) {

            picojson::object dep_obj = dep.get<picojson::object>();

            if (!(dep_obj["class"].is<std::string>()     && 
                    dep_obj["items"].is<picojson::array>() &&
                    dep_obj["maxOccupancy"].is<double>()    &&
                    dep_obj["occupancy"].is<double>())         ) return false;

            std::string dep_type      = dep_obj["class"].get<std::string>();
            picojson::array dep_items = dep_obj["items"].get<picojson::array>();
            float dep_maxOccupancy    = static_cast<float>(dep_obj["maxOccupancy"].get<double>());
            float dep_occupancy       = static_cast<float>(dep_obj["occupancy"].get<double>());

            IDepartmentPtr dep_ptr;
            
            if (dep_type == "ColdRoomDepartment") {

                dep_ptr = std::make_unique<ColdRoomDepartment>(ColdRoomDepartment(dep_maxOccupancy));

            } else if (dep_type == "HazardousDepartment") {

                dep_ptr = std::make_unique<HazardousDepartment>(HazardousDepartment(dep_maxOccupancy));

            } else if (dep_type == "OverSizeElectronicDepartment") {

                dep_ptr = std::make_unique<OverSizeElectronicDepartment>(OverSizeElectronicDepartment(dep_maxOccupancy));

            } else if (dep_type == "SmallElectronicDepartment") {

                dep_ptr = std::make_unique<SmallElectronicDepartment>(SmallElectronicDepartment(dep_maxOccupancy));

            } else if (dep_type == "SpecialDepartment") {

                dep_ptr = std::make_unique<SpecialDepartment>(SpecialDepartment(dep_maxOccupancy));

            } else {

                return false;

            }

            for (auto item : dep_items) {

                picojson::object item_obj = item.get<picojson::object>();

                if (!(item_obj["class"].is<std::string>()     &&
                        item_obj["flags"].is<picojson::array>() &&
                        item_obj["name"].is<std::string>()      &&
                        item_obj["size"].is<double>()               )) return false;

                std::string item_class     = item_obj["class"].get<std::string>();
                picojson::array item_flags = item_obj["flags"].get<picojson::array>();
                std::string item_name      = item_obj["name"].get<std::string>();
                float item_size            = static_cast<float>(item_obj["size"].get<double>());

                IProductPtr item_ptr;

                if (item_class == "AcetoneBarrel") {

                    item_ptr = std::make_unique<AcetoneBarrel>(AcetoneBarrel(item_name, item_size));

                } else if (item_class == "AstronautsIceCream") {

                    item_ptr = std::make_unique<AstronautsIceCream>(AstronautsIceCream(item_name, item_size));

                } else if (item_class == "ElectronicParts") {

                    item_ptr = std::make_unique<ElectronicParts>(ElectronicParts(item_name, item_size));

                } else if (item_class == "ExplosiveBarrel") {

                    item_ptr = std::make_unique<ExplosiveBarrel>(ExplosiveBarrel(item_name, item_size));

                } else if (item_class == "GlassWare") {

                    item_ptr = std::make_unique<GlassWare>(GlassWare(item_name, item_size));

                } else if (item_class == "IndustrialServerRack") {

                    item_ptr = std::make_unique<IndustrialServerRack>(IndustrialServerRack(item_name, item_size));

                } else if (item_class == "TV") {

                    item_ptr = std::make_unique<TV>(TV(item_name, item_size));

                } else {

                    return false;

                }

                using namespace magic_enum::bitwise_operators;
                ProductLabelFlags flags = static_cast<ProductLabelFlags>(0);

                std::map<std::string, ProductLabelFlags> available{{"fireHazardous", ProductLabelFlags::fireHazardous},
                                                                   {"explosives", ProductLabelFlags::explosives},
                                                                   {"fragile", ProductLabelFlags::fragile},
                                                                   {"upWard", ProductLabelFlags::upWard},
                                                                   {"keepDry", ProductLabelFlags::keepDry},
                                                                   {"handleWithCare", ProductLabelFlags::handleWithCare},
                                                                   {"keepFrozen", ProductLabelFlags::keepFrozen},
                                                                   {"esdSensitive", ProductLabelFlags::esdSensitive}};

                for (auto flag : item_flags) {

                    flags = (flags | available[flag.get<std::string>()]);

                }

                if (item_ptr->itemFlags() != flags) {

                    return false;

                }

                dep_ptr->addItem(std::move(item_ptr));

            }

            if (dep_ptr->getOccupancy() != dep_occupancy) {

                return false;

            }

            departments_.push_back(std::move(dep_ptr));

        }

        return true;

    }

}