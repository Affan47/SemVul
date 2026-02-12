bool DecimalQuantity::fitsInLong(bool ignoreFraction) const {
    if (isZero()) {
        return true;
    }
    if (scale < 0 && !ignoreFraction) {
        return false;
    }
    int magnitude = getMagnitude();
    if (magnitude < 18) {
        return true;
    }
    if (magnitude > 18) {
        return false;
    }


    for (int p = 0; p < precision; p++) {
        int8_t digit = getDigit(18 - p);
        static int8_t INT64_BCD[] = { 9, 2, 2, 3, 3, 7, 2, 0, 3, 6, 8, 5, 4, 7, 7, 5, 8, 0, 8 };
        if (digit < INT64_BCD[p]) {
            return true;
        } else if (digit > INT64_BCD[p]) {
            return false;
        }
    }

    return isNegative();
}
