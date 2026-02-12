LPCOLESTR Parser::AppendNameHints(LPCOLESTR leftStr, uint32 leftLen, LPCOLESTR rightStr, uint32 rightLen, uint32 *pNameLength, uint32 *pShortNameOffset, bool ignoreAddDotWithSpace, bool wrapInBrackets)
{
    Assert(rightStr != nullptr);
    Assert(leftLen  != 0 || wrapInBrackets);
    Assert(rightLen != 0 || wrapInBrackets);

    bool ignoreDot = rightStr[0] == _u('[') && !wrapInBrackets;
    uint32 totalLength = leftLen + rightLen + ((ignoreDot) ? 1 : 2);

    if (wrapInBrackets)
    {
        totalLength++;
    }
    WCHAR * finalName = AllocateStringOfLength(totalLength);

    if (leftStr != nullptr && leftLen != 0)
    {
        wcscpy_s(finalName, leftLen + 1, leftStr);
    }

    if (ignoreAddDotWithSpace)
    {
        finalName[leftLen++] = (OLECHAR)_u(' ');
    }


    else if (wrapInBrackets)
    {
        finalName[leftLen++] = (OLECHAR)_u('[');
        finalName[totalLength-2] = (OLECHAR)_u(']');
    }
    else if (!ignoreDot)
    {
        finalName[leftLen++] = (OLECHAR)_u('.');
    }

    js_wmemcpy_s(finalName + leftLen, rightLen, rightStr, rightLen);
    finalName[totalLength-1] = (OLECHAR)_u('\0');

    if (pNameLength != nullptr)
    {
        *pNameLength = totalLength - 1;
    }
    if (pShortNameOffset != nullptr)
    {
        *pShortNameOffset = leftLen;
    }

    return finalName;
}
