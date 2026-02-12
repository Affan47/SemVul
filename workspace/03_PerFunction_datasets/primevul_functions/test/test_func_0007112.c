DocumentSource::GetModPathsReturn DocumentSourceGroup::getModifiedPaths() const {


    StringMap<std::string> renames;
    for (std::size_t i = 0; i < _idExpressions.size(); ++i) {
        auto idExp = _idExpressions[i];
        auto pathToPutResultOfExpression =
            _idFieldNames.empty() ? "_id" : "_id." + _idFieldNames[i];
        auto computedPaths = idExp->getComputedPaths(pathToPutResultOfExpression);
        for (auto&& rename : computedPaths.renames) {
            renames[rename.first] = rename.second;
        }
    }

    return {DocumentSource::GetModPathsReturn::Type::kAllExcept,
            std::set<std::string>{},
            std::move(renames)};
}
