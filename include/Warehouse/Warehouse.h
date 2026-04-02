#pragma once

#include <Interfaces/IWarehouse.hpp>
#include <Interfaces/Aliases.hpp>
#include <Interfaces/IDepartment.hpp>
#include <Interfaces/IProduct.hpp>
#include <PicoJson/picojson.h>
#include <MagicEnum/magic_enum.hpp>
#include <Departments/DepartmentsList.hpp>
#include <Products/ProductsList.hpp>

using IProductPtr = warehouseInterface::IProductPtr;
using IDepartmentPtr = warehouseInterface::IDepartmentPtr;
using IWarehouse = warehouseInterface::IWarehouse;
using DeliveryReportJson = warehouseInterface::DeliveryReportJson;
using Order = warehouseInterface::Order;
using OrderJson = warehouseInterface::OrderJson;
using OccupancyReportJson = warehouseInterface::OccupancyReportJson;
using WarehouseStateJson = warehouseInterface::WarehouseStateJson;

namespace warehouse
{
class Warehouse : public IWarehouse
{

    public:
    
        Warehouse() {}

        void addDepartment(IDepartmentPtr) override;

        DeliveryReportJson newDelivery(std::vector<IProductPtr>) override;

        Order newOrder(const OrderJson &) override;

        OccupancyReportJson getOccupancyReport() const override;

        WarehouseStateJson saveWarehouseState() const override;

        bool loadWarehouseState(const WarehouseStateJson &) override;

};

}  // namespace warehouse