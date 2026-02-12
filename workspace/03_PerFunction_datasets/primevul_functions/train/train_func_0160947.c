int64_t DecimalQuantity::toLong(bool truncateIfOverflow) const {


    uint64_t result = 0L;
    int32_t upperMagnitude = std::min(scale + precision, lOptPos) - 1;
    if (truncateIfOverflow) {
        upperMagnitude = std::min(upperMagnitude, 17);
    }
    for (int32_t magnitude = upperMagnitude; magnitude >= 0; magnitude--) {
        result = result * 10 + getDigitPos(magnitude - scale);
    }
    if (isNegative()) {
        return static_cast<int64_t>(0LL - result);
    }
    return static_cast<int64_t>(result);
}
