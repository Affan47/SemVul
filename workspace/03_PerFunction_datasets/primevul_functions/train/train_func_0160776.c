DecimalQuantity &DecimalQuantity::setToInt(int32_t n) {
    setBcdToZero();
    flags = 0;
    if (n == INT32_MIN) {
        flags |= NEGATIVE_FLAG;

    } else if (n < 0) {
        flags |= NEGATIVE_FLAG;
        n = -n;
    }
    if (n != 0) {
        _setToInt(n);
        compact();
    }
    return *this;
}
