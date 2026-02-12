void DecimalQuantity::toDecNum(DecNum& output, UErrorCode& status) const {

    if (precision == 0) {
        output.setTo("0", status);
    }


    MaybeStackArray<uint8_t, 20> ubcd(precision);
    for (int32_t m = 0; m < precision; m++) {
        ubcd[precision - m - 1] = static_cast<uint8_t>(getDigitPos(m));
    }
    output.setTo(ubcd.getAlias(), precision, scale, isNegative(), status);
}
