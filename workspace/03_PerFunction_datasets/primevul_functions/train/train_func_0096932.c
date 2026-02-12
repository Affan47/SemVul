DocumentSourceGroup::rewriteGroupAsTransformOnFirstDocument() const {
    if (_idExpressions.size() != 1) {

        return nullptr;
    }

    auto fieldPathExpr = dynamic_cast<ExpressionFieldPath*>(_idExpressions.front().get());
    if (!fieldPathExpr || fieldPathExpr->isVariableReference()) {
        return nullptr;
    }

    const auto fieldPath = fieldPathExpr->getFieldPath();
    if (fieldPath.getPathLength() == 1) {


        invariant(fieldPath.getFieldName(0) == "CURRENT" || fieldPath.getFieldName(0) == "ROOT");
        return nullptr;
    }

    const auto groupId = fieldPath.tail().fullPath();


    for (auto&& accumulator : _accumulatedFields) {
        if (AccumulatorDocumentsNeeded::kFirstDocument !=
            accumulator.makeAccumulator()->documentsNeeded()) {
            return nullptr;
        }
    }

    std::vector<std::pair<std::string, boost::intrusive_ptr<Expression>>> fields;

    boost::intrusive_ptr<Expression> idField;


    if (_idFieldNames.empty()) {
        idField = ExpressionFieldPath::deprecatedCreate(pExpCtx.get(), groupId);
    } else {
        invariant(_idFieldNames.size() == 1);
        idField = ExpressionObject::create(pExpCtx.get(),
                                           {{_idFieldNames.front(), _idExpressions.front()}});
    }
    fields.push_back(std::make_pair("_id", idField));

    for (auto&& accumulator : _accumulatedFields) {
        fields.push_back(std::make_pair(accumulator.fieldName, accumulator.expr.argument));


    }

    return GroupFromFirstDocumentTransformation::create(pExpCtx, groupId, std::move(fields));
}
