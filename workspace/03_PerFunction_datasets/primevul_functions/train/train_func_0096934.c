void DocumentSourceGroup::freeMemory() {
    invariant(_groups);
    for (auto&& group : *_groups) {
        for (size_t i = 0; i < group.second.size(); i++) {

            _memoryTracker.update(_accumulatedFields[i].fieldName,
                                  -1 * group.second[i]->getMemUsage());

            group.second[i]->reduceMemoryConsumptionIfAble();


            _memoryTracker.update(_accumulatedFields[i].fieldName, group.second[i]->getMemUsage());
        }
    }
}
