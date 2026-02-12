intrusive_ptr<Expression> ExpressionSetIsSubset::optimize() {

    intrusive_ptr<Expression> optimized = ExpressionNary::optimize();


    if (optimized.get() != this)
        return optimized;

    if (ExpressionConstant* ec = dynamic_cast<ExpressionConstant*>(vpOperand[1].get())) {
        const Value rhs = ec->getValue();
        uassert(17311,
                str::stream() << "both operands of $setIsSubset must be arrays. Second "
                              << "argument is of type: "
                              << typeName(rhs.getType()),
                rhs.isArray());

        intrusive_ptr<Expression> optimizedWithConstant(
            new Optimized(this->getExpressionContext(),
                          arrayToSet(rhs, getExpressionContext()->getValueComparator()),
                          vpOperand));
        return optimizedWithConstant;
    }
    return optimized;
}
