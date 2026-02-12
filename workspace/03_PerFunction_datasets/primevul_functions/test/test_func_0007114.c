DepsTracker::State GroupFromFirstDocumentTransformation::addDependencies(DepsTracker* deps) const {
    for (auto&& expr : _accumulatorExprs) {
        expr.second->addDependencies(deps);
    }


    return DepsTracker::State::EXHAUSTIVE_ALL;
}
