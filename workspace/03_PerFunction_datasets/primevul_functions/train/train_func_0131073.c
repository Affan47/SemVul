intrusive_ptr<ExpressionObject> ExpressionObject::parse(
    const boost::intrusive_ptr<ExpressionContext>& expCtx,
    BSONObj obj,
    const VariablesParseState& vps) {

    stdx::unordered_set<string> specifiedFields;

    vector<pair<string, intrusive_ptr<Expression>>> expressions;
    for (auto&& elem : obj) {


        FieldPath::uassertValidFieldName(elem.fieldNameStringData());

        auto fieldName = elem.fieldName();
        uassert(16406,
                str::stream() << "duplicate field name specified in object literal: "
                              << obj.toString(),
                specifiedFields.find(fieldName) == specifiedFields.end());
        specifiedFields.insert(fieldName);
        expressions.emplace_back(fieldName, parseOperand(expCtx, elem, vps));
    }

    return new ExpressionObject{expCtx, std::move(expressions)};
}
