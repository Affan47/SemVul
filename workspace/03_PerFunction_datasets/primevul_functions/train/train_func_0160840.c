void DecimalQuantity::roundToIncrement(double roundingIncrement, RoundingMode roundingMode,
                                       int32_t maxFrac, UErrorCode& status) {

    if (roundingIncrement == 0.05) {
        roundToMagnitude(-2, roundingMode, true, status);
        roundToMagnitude(-maxFrac, roundingMode, false, status);
        return;
    } else if (roundingIncrement == 0.5) {
        roundToMagnitude(-1, roundingMode, true, status);
        roundToMagnitude(-maxFrac, roundingMode, false, status);
        return;
    }


    roundToInfinity();
    double temp = toDouble();
    temp /= roundingIncrement;

    DecimalQuantity dq;
    dq.setToDouble(temp);
    dq.roundToMagnitude(0, roundingMode, status);
    temp = dq.toDouble();
    temp *= roundingIncrement;
    setToDouble(temp);


    roundToMagnitude(-maxFrac, roundingMode, status);
}
