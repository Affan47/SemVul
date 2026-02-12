void DocumentSourceGroup::doDispose() {

    _groups = pExpCtx->getValueComparator().makeUnorderedValueMap<Accumulators>();
    _sorterIterator.reset();


    groupsIterator = _groups->end();
}
