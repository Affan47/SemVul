DocumentSource::GetModPathsReturn GroupFromFirstDocumentTransformation::getModifiedPaths() const {

    return {DocumentSource::GetModPathsReturn::Type::kAllPaths, std::set<std::string>{}, {}};
}
