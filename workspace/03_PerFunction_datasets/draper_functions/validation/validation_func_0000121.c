_PyUnicode_ToTitlecase(register Py_UCS4 ch)
{
    const _PyUnicode_TypeRecord *ctype = gettyperecord(ch);

    if (ctype->flags & EXTENDED_CASE_MASK)
        return _PyUnicode_ExtendedCase[ctype->title & 0xFFFF];
    return ch + ctype->title;
}
