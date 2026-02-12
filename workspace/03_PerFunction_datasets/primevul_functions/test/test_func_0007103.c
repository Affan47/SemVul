MONGO_COMPILER_NOINLINE DocumentSource::GetNextResult DocumentSourceGroup::initializeSelf(
    GetNextResult input) {
    const size_t numAccumulators = _accumulatedFields.size();

    for (; input.isAdvanced(); input = pSource->getNext()) {
        if (_memoryTracker.shouldSpillWithAttemptToSaveMemory([this]() { return freeMemory(); })) {
            _sortedFiles.push_back(spill());
        }


        auto rootDocument = input.releaseDocument();
        Value id = computeId(rootDocument);


        const size_t oldSize = _groups->size();
        vector<intrusive_ptr<AccumulatorState>>& group = (*_groups)[id];
        const bool inserted = _groups->size() != oldSize;

        if (inserted) {
            _memoryTracker.memoryUsageBytes += id.getApproximateSize();


            Value expandedId = expandId(id);
            Document idDoc =
                expandedId.getType() == BSONType::Object ? expandedId.getDocument() : Document();
            group.reserve(numAccumulators);
            for (auto&& accumulatedField : _accumulatedFields) {
                auto accum = accumulatedField.makeAccumulator();
                Value initializerValue =
                    accumulatedField.expr.initializer->evaluate(idDoc, &pExpCtx->variables);
                accum->startNewGroup(initializerValue);
                group.push_back(accum);
            }
        } else {
            for (auto&& groupObj : group) {

                _memoryTracker.memoryUsageBytes -= groupObj->memUsageForSorter();
            }
        }


        dassert(numAccumulators == group.size());

        for (size_t i = 0; i < numAccumulators; i++) {
            group[i]->process(
                _accumulatedFields[i].expr.argument->evaluate(rootDocument, &pExpCtx->variables),
                _doingMerge);

            _memoryTracker.memoryUsageBytes += group[i]->memUsageForSorter();
        }

        if (kDebugBuild && !storageGlobalParams.readOnly) {

            if (!inserted &&
                !pExpCtx->inMongos &&
                !_memoryTracker.allowDiskUse &&
                _sortedFiles.size() < 20) {

                _sortedFiles.push_back(spill());
            }
        }
    }

    switch (input.getStatus()) {
        case DocumentSource::GetNextResult::ReturnStatus::kAdvanced: {
            MONGO_UNREACHABLE;
        }
        case DocumentSource::GetNextResult::ReturnStatus::kPauseExecution: {
            return input;
        }
        case DocumentSource::GetNextResult::ReturnStatus::kEOF: {

            if (!_sortedFiles.empty()) {
                _spilled = true;
                if (!_groups->empty()) {
                    _sortedFiles.push_back(spill());
                }


                _groups = pExpCtx->getValueComparator().makeUnorderedValueMap<Accumulators>();

                _sorterIterator.reset(Sorter<Value, Value>::Iterator::merge(
                    _sortedFiles, SortOptions(), SorterComparator(pExpCtx->getValueComparator())));


                _currentAccumulators.reserve(numAccumulators);
                for (auto&& accumulatedField : _accumulatedFields) {
                    _currentAccumulators.push_back(accumulatedField.makeAccumulator());
                }

                verify(_sorterIterator->more());
                _firstPartOfNextGroup = _sorterIterator->next();
            } else {

                groupsIterator = _groups->begin();
            }


            _initialized = true;
            return input;
        }
    }
    MONGO_UNREACHABLE;
}
