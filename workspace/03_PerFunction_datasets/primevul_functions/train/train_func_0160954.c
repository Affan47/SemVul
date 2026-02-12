void DecimalQuantity::convertToAccurateDouble() {
    U_ASSERT(origDouble != 0);
    int32_t delta = origDelta;


    char buffer[DoubleToStringConverter::kBase10MaximalLength + 1];
    bool sign;
    int32_t length;
    int32_t point;
    DoubleToStringConverter::DoubleToAscii(
        origDouble,
        DoubleToStringConverter::DtoaMode::SHORTEST,
        0,
        buffer,
        sizeof(buffer),
        &sign,
        &length,
        &point
    );

    setBcdToZero();
    readDoubleConversionToBcd(buffer, length, point);
    scale += delta;
    explicitExactDouble = true;
}
