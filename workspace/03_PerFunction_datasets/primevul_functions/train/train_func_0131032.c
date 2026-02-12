Value ExpressionTrunc::evaluateNumericArg(const Value& numericArg) const {

    switch (numericArg.getType()) {
        case NumberDecimal:
            return Value(numericArg.getDecimal().quantize(Decimal128::kNormalizedZero,
                                                          Decimal128::kRoundTowardZero));
        case NumberDouble:
            return Value(std::trunc(numericArg.getDouble()));
        default:
            return numericArg;
    }
}
