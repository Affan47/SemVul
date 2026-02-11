doIt(const Move& m, bool undo)
{
    if(m.isNullMove())
    {
        if(undo)
        {
            BitBoard::undoMove(m);
        }
        else
        {
            BitBoard::doMove(m);
        }

        return true;
    }

    if(!m.isLegal())
    {
        return false;
    }

    CastlingRights oldCastlingRights = castlingRights();

    hashEpSquare();
    hashPiece(m.from(), m.pieceMoved());
    if(m.isPromotion())
    {
        hashPiece(m.to(), m.promotedPiece());
    }
    else
    {
        hashPiece(m.to(), m.pieceMoved());
    }
    if(m.isCastling())
    {
        Piece p = (m == White ? WhiteRook : BlackRook);
        hashPiece(m.castlingRookFrom(), p);
        hashPiece(m.castlingRookTo(), p);
    }
    else if(m.isEnPassant())
    {
        if(m == White)
        {
            hashPiece(m.to() - 8, m.capturedPiece());
        }
        else
        {
            hashPiece(m.to() + 8, m.capturedPiece());
        }
    }
    else if(m.capturedPiece())
    {
        hashPiece(m.to(), m.capturedPiece());
    }

    if(undo)
    {
        BitBoard::undoMove(m);
    }
    else
    {
        BitBoard::doMove(m);
    }

    hashToMove();
    hashEpSquare();
    hashCastlingRights(oldCastlingRights);
    return true;
}
