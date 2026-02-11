PrintCompactStr(char * cboard)
{
    for(unsigned int i = 0; i < 32; ++i)
    {
        unsigned int i2 = i << 1;
        cboard[i] = (unsigned char)(Board[i2] << 4) | Board[i2 + 1];
    }
    cboard[32] = 1 + ToMove;
    cboard[33] = 1 + Castling;


    squareT ep = EPTarget;
    if(ToMove == WHITE)
    {
        if(Board[square_Move(ep, DOWN_LEFT)] != WP  &&
                Board[square_Move(ep, DOWN_RIGHT)] != WP)
        {
            ep = NULL_SQUARE;
        }

    }
    else
    {
        if(Board[square_Move(ep, UP_LEFT)] != BP  &&
                Board[square_Move(ep, UP_RIGHT)] != BP)
        {
            ep = NULL_SQUARE;
        }

    }
    cboard[34] = 1 + ep;
    cboard[35] = 0;
}
