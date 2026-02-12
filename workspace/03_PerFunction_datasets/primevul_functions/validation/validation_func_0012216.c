intrusive_ptr<Expression> Expression::parseObject(ExpressionContext* const expCtx,
                                                  BSONObj obj,
                                                  const VariablesParseState& vps) {
    if (obj.isEmpty()) {
        return ExpressionObject::create(expCtx, {});
    }

    if (obj.firstElementFieldName()[0] == '$') {

        return parseExpression(expCtx, obj, vps);
    }

    return ExpressionObject::parse(expCtx, obj, vps);
}
