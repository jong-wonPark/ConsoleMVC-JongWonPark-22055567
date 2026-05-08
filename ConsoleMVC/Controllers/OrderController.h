#pragma once
#include "../Services/OrderService.h"
#include "../Repositories/CustomerRepository.h"
#include "../Repositories/ProductRepository.h"
#include "../Views/OrderView.h"

class OrderController {
public:
    OrderController(OrderService& orderService,
                    CustomerRepository& customerRepo,
                    ProductRepository& productRepo);

    void run();

private:
    OrderService& orderService_;
    CustomerRepository& customerRepo_;
    ProductRepository& productRepo_;
    OrderView view_;

    void handleCreateOrder();
    void handleListOrders();
    void handleApproveOrder();
    void handleRejectOrder();
    void handleProcessShipment();
    void handleCompleteShipment();
    void handleViewDetail();
};
