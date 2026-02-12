shared_ptr<Sorter<Value, Value>::Iterator> DocumentSourceGroup::spill() {
    _stats.usedDisk = true;
    vector<const GroupsMap::value_type*> ptrs;
    ptrs.reserve(_groups->size());
    for (GroupsMap::const_iterator it = _groups->begin(), end = _groups->end(); it != end; ++it) {
        ptrs.push_back(&*it);
    }

    stable_sort(ptrs.begin(), ptrs.end(), SpillSTLComparator(pExpCtx->getValueComparator()));

    SortedFileWriter<Value, Value> writer(SortOptions().TempDir(pExpCtx->tempDir), _file);
    switch (_accumulatedFields.size()) {
        case 0:
            for (size_t i = 0; i < ptrs.size(); i++) {
                writer.addAlreadySorted(ptrs[i]->first, Value());
            }
            break;

        case 1:
            for (size_t i = 0; i < ptrs.size(); i++) {
                writer.addAlreadySorted(ptrs[i]->first,
                                        ptrs[i]->second[0]->getValue(true));
            }
            break;

        default:
            for (size_t i = 0; i < ptrs.size(); i++) {
                vector<Value> accums;
                for (size_t j = 0; j < ptrs[i]->second.size(); j++) {
                    accums.push_back(ptrs[i]->second[j]->getValue(true));
                }
                writer.addAlreadySorted(ptrs[i]->first, Value(std::move(accums)));
            }
            break;
    }

    auto& metricsCollector = ResourceConsumption::MetricsCollector::get(pExpCtx->opCtx);
    metricsCollector.incrementKeysSorted(ptrs.size());
    metricsCollector.incrementSorterSpills(1);

    _groups->clear();


    for (auto accum : _accumulatedFields) {
        _memoryTracker.set(accum.fieldName, 0);
    }

    Sorter<Value, Value>::Iterator* iteratorPtr = writer.done();
    return shared_ptr<Sorter<Value, Value>::Iterator>(iteratorPtr);
}
