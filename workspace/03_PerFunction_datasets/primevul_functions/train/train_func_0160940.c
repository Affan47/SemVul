void DecimalQuantity::compact() {
    if (usingBytes) {
        int32_t delta = 0;
        for (; delta < precision && fBCD.bcdBytes.ptr[delta] == 0; delta++);
        if (delta == precision) {

            setBcdToZero();
            return;
        } else {

            shiftRight(delta);
        }


        int32_t leading = precision - 1;
        for (; leading >= 0 && fBCD.bcdBytes.ptr[leading] == 0; leading--);
        precision = leading + 1;


        if (precision <= 16) {
            switchStorage();
        }

    } else {
        if (fBCD.bcdLong == 0L) {

            setBcdToZero();
            return;
        }


        int32_t delta = 0;
        for (; delta < precision && getDigitPos(delta) == 0; delta++);
        fBCD.bcdLong >>= delta * 4;
        scale += delta;


        int32_t leading = precision - 1;
        for (; leading >= 0 && getDigitPos(leading) == 0; leading--);
        precision = leading + 1;
    }
}
