format(int64_t number,
                      UnicodeString& appendTo,
                      FieldPosition& fieldPosition,
                      AttrBuffer attrBuffer) const
{

    DigitList digits;


    fieldPosition.setBeginIndex(0);
    fieldPosition.setEndIndex(0);


    if (fRoundingIncrement != NULL
        || (fMultiplier > 0 && (number > U_INT64_MAX / fMultiplier || number < U_INT64_MIN / fMultiplier))
        || (fMultiplier < 0 && (number == U_INT64_MIN || -number > U_INT64_MAX / -fMultiplier || -number < U_INT64_MIN / -fMultiplier))
        )
    {
        digits.set(((double) number) * fMultiplier,
                   precision(FALSE),
                   !fUseExponentialNotation && !areSignificantDigitsUsed());
    }
    else
    {
        digits.set(number * fMultiplier, precision(TRUE));
    }

    return subformat(appendTo, fieldPosition, attrBuffer, digits, TRUE);
}
