void DecimalQuantity::appendDigit(int8_t value, int32_t leadingZeros, bool appendAsInteger) {
    U_ASSERT(leadingZeros >= 0);


    if (value == 0) {
        if (appendAsInteger && precision != 0) {
            scale += leadingZeros + 1;
        }
        return;
    }


    if (scale > 0) {
        leadingZeros += scale;
        if (appendAsInteger) {
            scale = 0;
        }
    }


    shiftLeft(leadingZeros + 1);
    setDigitPos(0, value);


    if (appendAsInteger) {
        scale += leadingZeros + 1;
    }
}
