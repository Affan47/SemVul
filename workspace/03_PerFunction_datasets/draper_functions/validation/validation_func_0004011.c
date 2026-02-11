getUint16(Uint16 &uintVal,
                                        const unsigned long pos)
{

    Uint16 *uintValues = NULL;
    errorFlag = getUint16Array(uintValues);

    if (errorFlag.good())
    {
        if (uintValues == NULL)
            errorFlag = EC_IllegalCall;
        else if (pos >= getVM())
            errorFlag = EC_IllegalParameter;
        else
            uintVal = uintValues[pos];
    }

    if (errorFlag.bad())
        uintVal = 0;
    return errorFlag;
}
