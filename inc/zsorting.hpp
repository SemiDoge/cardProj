#ifndef ZSORTING_H
#define ZSORTING_H

#include <vector>
#include <algorithm>
#include "../inc/entity.hpp"

void zidxSort(std::vector<std::shared_ptr<Entity>>& entities);
bool zComp(const std::shared_ptr<Entity> a, const std::shared_ptr<Entity> b);

#endif