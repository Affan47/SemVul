Formattable::operator=(const Formattable& source)
{
    if (this != &source)
    {

        dispose();


        fType = source.fType;
        switch (fType)
        {
        case kArray:

            fValue.fArrayAndCount.fCount = source.fValue.fArrayAndCount.fCount;
            fValue.fArrayAndCount.fArray = createArrayCopy(source.fValue.fArrayAndCount.fArray,
                                                           source.fValue.fArrayAndCount.fCount);
            break;
        case kString:

            fValue.fString = new UnicodeString(*source.fValue.fString);
            break;
        case kDouble:

            fValue.fDouble = source.fValue.fDouble;
            break;
        case kLong:
        case kInt64:

            fValue.fInt64 = source.fValue.fInt64;
            break;
        case kDate:

            fValue.fDate = source.fValue.fDate;
            break;
        case kObject:
            fValue.fObject = objectClone(source.fValue.fObject);
            break;
        }

        UErrorCode status = U_ZERO_ERROR;
        if (source.fDecimalQuantity != NULL) {
          fDecimalQuantity = new DecimalQuantity(*source.fDecimalQuantity);
        }
        if (source.fDecimalStr != NULL) {
            fDecimalStr = new CharString(*source.fDecimalStr, status);
            if (U_FAILURE(status)) {
                delete fDecimalStr;
                fDecimalStr = NULL;
            }
        }
    }
    return *this;
}
