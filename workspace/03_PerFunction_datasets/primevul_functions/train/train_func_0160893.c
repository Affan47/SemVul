double DecimalQuantity::toDouble() const {


    U_ASSERT(!isApproximate);

    if (isNaN()) {
        return NAN;
    } else if (isInfinite()) {
        return isNegative() ? -INFINITY : INFINITY;
    }


    StringToDoubleConverter converter(0, 0, 0, "", "");
    UnicodeString numberString = this->toScientificString();
    int32_t count;
    return converter.StringToDouble(
            reinterpret_cast<const uint16_t*>(numberString.getBuffer()),
            numberString.length(),
            &count);
}
