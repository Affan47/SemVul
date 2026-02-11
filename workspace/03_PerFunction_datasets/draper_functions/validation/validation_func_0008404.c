ReadFromCompactStr(const unsigned char * str)
{
    Clear();
    for(unsigned int i = 0; i < 32; ++i)
    {
        pieceT p = str[i] >> 4;
        if(p != EMPTY)
        {
            if(AddPiece(p, i * 2) != OK)
            {
                return ERROR_Corrupt;
            }
        }
        p = str[i] & 15;
        if(p != EMPTY)
        {
            if(AddPiece(p, i * 2 + 1) != OK)
            {
                return ERROR_Corrupt;
            }
        }
    }
    colorT toMove = str[32] - 1;
    if(toMove != WHITE  &&  toMove != BLACK)
    {
        return ERROR_Corrupt;
    }
    ToMove = toMove;
    Castling = str[33] - 1;
    EPTarget = str[34] - 1;
    return OK;
}
