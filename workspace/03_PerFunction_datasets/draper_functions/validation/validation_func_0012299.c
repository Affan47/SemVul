tok_is_string_character(wchar_t c, bool is_first)
{
    switch (c)
    {

        case L'\0':
        case L' ':
        case L'\n':
        case L'|':
        case L'\t':
        case L';':
        case L'#':
        case L'\r':
        case L'<':
        case L'>':
        case L'&':
            return false;


        case L'^':
            return ! is_first;

        default:
            return true;
    }
}
