Value ExpressionMod::evaluate(const Document& root) const {
    Value lhs = vpOperand[0]->evaluate(root);
    Value rhs = vpOperand[1]->evaluate(root);

    BSONType leftType = lhs.getType();
    BSONType rightType = rhs.getType();

    if (lhs.numeric() && rhs.numeric()) {
        auto assertNonZero = [](bool isZero) { uassert(16610, "can't $mod by zero", !isZero); };


        if (leftType == NumberDecimal || rightType == NumberDecimal) {
            Decimal128 left = lhs.coerceToDecimal();
            Decimal128 right = rhs.coerceToDecimal();
            assertNonZero(right.isZero());

            return Value(left.modulo(right));
        }


        double right = rhs.coerceToDouble();
        assertNonZero(right == 0);

        if (leftType == NumberDouble || (rightType == NumberDouble && !rhs.integral())) {


            double left = lhs.coerceToDouble();
            return Value(fmod(left, right));
        } else if (leftType == NumberLong || rightType == NumberLong) {

            long long left = lhs.coerceToLong();
            long long rightLong = rhs.coerceToLong();
            return Value(left % rightLong);
        }


        int left = lhs.coerceToInt();
        int rightInt = rhs.coerceToInt();
        return Value(left % rightInt);
    } else if (lhs.nullish() || rhs.nullish()) {
        return Value(BSONNULL);
    } else {
        uasserted(16611,
                  str::stream() << "$mod only supports numeric types, not "
                                << typeName(lhs.getType())
                                << " and "
                                << typeName(rhs.getType()));
    }
}
