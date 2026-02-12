DocumentSource::GetNextResult DocumentSourceGroup::getNextSpilled() {

    if (!_sorterIterator)
        return GetNextResult::makeEOF();

    _currentId = _firstPartOfNextGroup.first;
    const size_t numAccumulators = _accumulatedFields.size();


    Value expandedId = expandId(_currentId);
    Document idDoc =
        expandedId.getType() == BSONType::Object ? expandedId.getDocument() : Document();
    for (size_t i = 0; i < numAccumulators; ++i) {
        Value initializerValue =
            _accumulatedFields[i].expr.initializer->evaluate(idDoc, &pExpCtx->variables);
        _currentAccumulators[i]->startNewGroup(initializerValue);
    }

    while (pExpCtx->getValueComparator().evaluate(_currentId == _firstPartOfNextGroup.first)) {


        switch (numAccumulators) {
            case 1:
                _currentAccumulators[0]->process(_firstPartOfNextGroup.second, true);
            case 0:
                break;
            default: {
                const vector<Value>& accumulatorStates = _firstPartOfNextGroup.second.getArray();
                for (size_t i = 0; i < numAccumulators; i++) {
                    _currentAccumulators[i]->process(accumulatorStates[i], true);
                }
            }
        }

        if (!_sorterIterator->more()) {
            dispose();
            break;
        }

        _firstPartOfNextGroup = _sorterIterator->next();
    }

    return makeDocument(_currentId, _currentAccumulators, pExpCtx->needsMerge);
}
