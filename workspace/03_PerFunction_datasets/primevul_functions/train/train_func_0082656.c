Value ExpressionPow::evaluate(const Document& root) const {
    Value baseVal = vpOperand[0]->evaluate(root);
    Value expVal = vpOperand[1]->evaluate(root);
    if (baseVal.nullish() || expVal.nullish())
        return Value(BSONNULL);

    BSONType baseType = baseVal.getType();
    BSONType expType = expVal.getType();

    uassert(28762,
            str::stream() << "$pow's base must be numeric, not " << typeName(baseType),
            baseVal.numeric());
    uassert(28763,
            str::stream() << "$pow's exponent must be numeric, not " << typeName(expType),
            expVal.numeric());

    auto checkNonZeroAndNeg = [](bool isZeroAndNeg) {
        uassert(28764, "$pow cannot take a base of 0 and a negative exponent", !isZeroAndNeg);
    };


    if (baseType == NumberDecimal || expType == NumberDecimal) {
        Decimal128 baseDecimal = baseVal.coerceToDecimal();
        Decimal128 expDecimal = expVal.coerceToDecimal();
        checkNonZeroAndNeg(baseDecimal.isZero() && expDecimal.isNegative());
        return Value(baseDecimal.power(expDecimal));
    }


    double baseDouble = baseVal.coerceToDouble();
    double expDouble = expVal.coerceToDouble();
    checkNonZeroAndNeg(baseDouble == 0 && expDouble < 0);


    if (baseType == NumberDouble || expType == NumberDouble) {
        return Value(std::pow(baseDouble, expDouble));
    }


    auto representableAsLong = [](long long base, long long exp) {


        if (exp < 0 || exp > 63) {
            return std::abs(base) == 1 || base == 0;
        }

        struct MinMax {
            long long min;
            long long max;
        };


        static const MinMax kBaseLimits[] = {
            {std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()},
            {std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()},
            {-3037000499LL, 3037000499LL},
            {-2097152, 2097151},
            {-55108, 55108},
            {-6208, 6208},
            {-1448, 1448},
            {-512, 511},
            {-234, 234},
            {-128, 127},
            {-78, 78},
            {-52, 52},
            {-38, 38},
            {-28, 28},
            {-22, 22},
            {-18, 18},
            {-15, 15},
            {-13, 13},
            {-11, 11},
            {-9, 9},
            {-8, 8},
            {-8, 7},
            {-7, 7},
            {-6, 6},
            {-6, 6},
            {-5, 5},
            {-5, 5},
            {-5, 5},
            {-4, 4},
            {-4, 4},
            {-4, 4},
            {-4, 4},
            {-3, 3},
            {-3, 3},
            {-3, 3},
            {-3, 3},
            {-3, 3},
            {-3, 3},
            {-3, 3},
            {-3, 3},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 2},
            {-2, 1}};

        return base >= kBaseLimits[exp].min && base <= kBaseLimits[exp].max;
    };

    long long baseLong = baseVal.getLong();
    long long expLong = expVal.getLong();


    if (!representableAsLong(baseLong, expLong)) {
        return Value(std::pow(baseLong, expLong));
    }

    long long result = 1;


    for (int i = 0; i < expLong; i++) {
        result *= baseLong;
    }

    if (baseType == NumberLong || expType == NumberLong) {
        return Value(result);
    }
    return Value::createIntOrLong(result);
}
