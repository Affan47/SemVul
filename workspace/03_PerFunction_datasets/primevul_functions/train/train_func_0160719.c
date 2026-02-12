bool DecimalQuantity::adjustMagnitude(int32_t delta) {
    if (precision != 0) {

        bool overflow = uprv_add32_overflow(scale, delta, &scale);
        overflow = uprv_add32_overflow(origDelta, delta, &origDelta) || overflow;

        int32_t dummy;
        overflow = overflow || uprv_add32_overflow(scale, precision, &dummy);
        return overflow;
    }
    return false;
}
