AsMatchExactWord (
    char                    *Word,
    UINT32                  WordLength)
{
    char                    NextChar;
    char                    PrevChar;


    NextChar = Word[WordLength];
    PrevChar = * (Word -1);

    if (isalnum ((int) NextChar) ||
        (NextChar == '_')  ||
        isalnum ((int) PrevChar) ||
        (PrevChar == '_'))
    {
        return (FALSE);
    }

    return (TRUE);
}
