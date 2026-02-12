intrusive_ptr<Expression> Expression::parseExpression(ExpressionContext* const expCtx,
                                                      BSONObj obj,
                                                      const VariablesParseState& vps) {
    uassert(15983,
            str::stream() << "An object representing an expression must have exactly one "
                             "field: "
                          << obj.toString(),
            obj.nFields() == 1);


    const char* opName = obj.firstElementFieldName();
    auto it = parserMap.find(opName);
    uassert(ErrorCodes::InvalidPipelineOperator,
            str::stream() << "Unrecognized expression '" << opName << "'",
            it != parserMap.end());


    auto& entry = it->second;
    uassert(ErrorCodes::QueryFeatureNotAllowed,


            str::stream() << opName
                          << " is not allowed in the current feature compatibility version. See "
                          << feature_compatibility_version_documentation::kCompatibilityLink
                          << " for more information.",
            !expCtx->maxFeatureCompatibilityVersion || !entry.requiredMinVersion ||
                (*entry.requiredMinVersion <= *expCtx->maxFeatureCompatibilityVersion));
    return entry.parser(expCtx, obj.firstElement(), vps);
}
