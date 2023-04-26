#include "../inc/zsorting.hpp"

void zidxSort(std::vector<std::shared_ptr<Entity>>& entities) {
    std::sort(entities.begin(), entities.end(), zComp);

    int i = 0;
    for(std::shared_ptr<Entity> e : entities) {
        Logger::log(fmt::format("[{}]: Z:{} ({})", i, e->GetZIndex(), e->GetEntityLabel()), logSeverity::TRACE);
        i++;
    }
}

bool zComp(const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b) {
    return a->GetZIndex() < b->GetZIndex();
}