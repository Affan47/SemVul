Value ExpressionMultiply::evaluate(const Document& root) const {


    double doubleProduct = 1;
    long long longProduct = 1;
    Decimal128 decimalProduct;

    BSONType productType = NumberInt;

    const size_t n = vpOperand.size();
    for (size_t i = 0; i < n; ++i) {
        Value val = vpOperand[i]->evaluate(root);

        if (val.numeric()) {
            BSONType oldProductType = productType;
            productType = Value::getWidestNumeric(productType, val.getType());
            if (productType == NumberDecimal) {

                if (oldProductType != NumberDecimal) {
                    decimalProduct = oldProductType == NumberDouble
                        ? Decimal128(doubleProduct, Decimal128::kRoundTo15Digits)
                        : Decimal128(static_cast<int64_t>(longProduct));
                }
                decimalProduct = decimalProduct.multiply(val.coerceToDecimal());
            } else {
                doubleProduct *= val.coerceToDouble();
                if (mongoSignedMultiplyOverflow64(longProduct, val.coerceToLong(), &longProduct)) {

                    productType = NumberDouble;
                }
            }
        } else if (val.nullish()) {
            return Value(BSONNULL);
        } else {
            uasserted(16555,
                      str::stream() << "$multiply only supports numeric types, not "
                                    << typeName(val.getType()));
        }
    }

    if (productType == NumberDouble)
        return Value(doubleProduct);
    else if (productType == NumberLong)
        return Value(longProduct);
    else if (productType == NumberInt)
        return Value::createIntOrLong(longProduct);
    else if (productType == NumberDecimal)
        return Value(decimalProduct);
    else
        massert(16418, "$multiply resulted in a non-numeric type", false);
}
