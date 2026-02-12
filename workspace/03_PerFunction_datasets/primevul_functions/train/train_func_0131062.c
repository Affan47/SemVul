intrusive_ptr<Expression> ExpressionFieldPath::optimize() {
    if (_variable == Variables::kRemoveId) {

        return ExpressionConstant::create(getExpressionContext(), Value());
    }

    if (getExpressionContext()->variables.hasConstantValue(_variable)) {
        return ExpressionConstant::create(getExpressionContext(), evaluate(Document()));
    }

    return intrusive_ptr<Expression>(this);
}
