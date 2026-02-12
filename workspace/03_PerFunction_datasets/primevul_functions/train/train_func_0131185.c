intrusive_ptr<Expression> Expression::parseExpression(
    const boost::intrusive_ptr<ExpressionContext>& expCtx,
    BSONObj obj,
    const VariablesParseState& vps) {
    uassert(15983,
            str::stream() << "An object representing an expression must have exactly one "
                             "field: "
                          << obj.toString(),
            obj.nFields() == 1);


    const char* opName = obj.firstElementFieldName();
    auto op = parserMap.find(opName);
    uassert(ErrorCodes::InvalidPipelineOperator,
            str::stream() << "Unrecognized expression '" << opName << "'",
            op != parserMap.end());
    return op->second(expCtx, obj.firstElement(), vps);
}
