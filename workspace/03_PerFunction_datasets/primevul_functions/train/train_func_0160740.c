int8_t DecimalQuantity::getDigit(int32_t magnitude) const {


    U_ASSERT(!isApproximate);

    return getDigitPos(magnitude - scale);
}
