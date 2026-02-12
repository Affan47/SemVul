Value ExpressionLet::evaluate(const Document& root) const {
    for (const auto& item : _variables) {


        getExpressionContext()->variables.setValue(item.first,
                                                   item.second.expression->evaluate(root));
    }

    return _subExpression->evaluate(root);
}
