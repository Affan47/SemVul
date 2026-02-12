DecimalQuantity &DecimalQuantity::setToDouble(double n) {
    setBcdToZero();
    flags = 0;

    if (std::signbit(n)) {
        flags |= NEGATIVE_FLAG;
        n = -n;
    }
    if (std::isnan(n) != 0) {
        flags |= NAN_FLAG;
    } else if (std::isfinite(n) == 0) {
        flags |= INFINITY_FLAG;
    } else if (n != 0) {
        _setToDoubleFast(n);
        compact();
    }
    return *this;
}
