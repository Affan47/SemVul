intrusive_ptr<Expression> parseIdExpression(const intrusive_ptr<ExpressionContext>& expCtx,
                                            BSONElement groupField,
                                            const VariablesParseState& vps) {
    if (groupField.type() == Object) {

        if (groupField.Obj().isEmpty()) {
            return ExpressionConstant::create(expCtx, Value(groupField));
        }

        const BSONObj idKeyObj = groupField.Obj();
        if (idKeyObj.firstElementFieldName()[0] == '$') {

            return Expression::parseObject(expCtx, idKeyObj, vps);
        } else {
            for (auto&& field : idKeyObj) {
                uassert(17390,
                        "$group does not support inclusion-style expressions",
                        !field.isNumber() && field.type() != Bool);
            }
            return ExpressionObject::parse(expCtx, idKeyObj, vps);
        }
    } else {
        return Expression::parseOperand(expCtx, groupField, vps);
    }
}
