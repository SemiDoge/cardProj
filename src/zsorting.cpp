#include "../inc/zsorting.hpp"

void zidxSort(std::vector<std::shared_ptr<Entity>>& entities) {
    Logger::log(fmt::format("Sorting rendering precedence."), logSeverity::INFO);
    std::sort(entities.begin(), entities.end(), zComp);
}

bool zComp(const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) {
    return a->GetZIndex() < b->GetZIndex();
}