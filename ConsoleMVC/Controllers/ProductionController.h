#pragma once
#include "../Services/ProductionService.h"
#include "../Repositories/ProductRepository.h"
#include "../Views/ProductionView.h"

class ProductionController {
public:
    ProductionController(ProductionService& productionService,
                         ProductRepository& productRepo);

    void run();

private:
    ProductionService& productionService_;
    ProductRepository& productRepo_;
    ProductionView view_;

    void handleCreateOrder();
    void handleViewAll();
    void handleStartProduction();
    void handlePauseProduction();
    void handleUpdateProgress();
    void handleCompleteProduction();
};
