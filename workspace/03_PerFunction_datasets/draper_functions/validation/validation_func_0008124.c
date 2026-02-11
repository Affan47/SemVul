UndoSimpleMove(simpleMoveT * m)
{
    ASSERT(m != NULL);
    squareT from = m->from;
    squareT to = m->to;
    pieceT p = Board[to];
    EPTarget = m->epSquare;
    Castling = m->castleFlags;
    HalfMoveClock = m->oldHalfMoveClock;
    PlyCounter--;
    ToMove = color_Flip(ToMove);
    m->pieceNum = ListPos[to];


    if(isNullMove(m))
    {
        return;
    }


    if(m->capturedPiece != EMPTY)
    {
        colorT c = color_Flip(ToMove);
        ListPos[List[c][m->capturedNum]] = Count[c];
        ListPos[m->capturedSquare] = m->capturedNum;
        List[c][Count[c]] = List[c][m->capturedNum];
        List[c][m->capturedNum] = m->capturedSquare;
        Material[m->capturedPiece]++;
        Count[c]++;
    }


    if(m->promote != EMPTY)
    {
        Material[p]--;
        RemoveFromBoard(p, to);
        p = piece_Make(ToMove, PAWN);
        Material[p]++;
        AddToBoard(p, to);
    }


    List[ToMove][m->pieceNum] = from;
    ListPos[from] = m->pieceNum;
    RemoveFromBoard(p, to);
    AddToBoard(p, from);
    if(m->capturedPiece != EMPTY)
    {
        AddToBoard(m->capturedPiece, m->capturedSquare);
    }


    if((piece_Type(p) == KING) && square_Fyle(from) == E_FYLE
            && (square_Fyle(to) == C_FYLE || square_Fyle(to) == G_FYLE))
    {
        squareT rookfrom, rookto;
        pieceT rook = (ToMove == WHITE ? WR : BR);
        if(square_Fyle(to) == C_FYLE)
        {
            rookfrom = to - 2;
            rookto = to + 1;
        }
        else
        {
            rookfrom = to + 1;
            rookto = to - 1;
        }
        ListPos[rookfrom] = ListPos[rookto];
        List[ToMove][ListPos[rookto]] = rookfrom;
        RemoveFromBoard(rook, rookto);
        AddToBoard(rook, rookfrom);
    }

#ifdef ASSERTIONS
    if(AssertPos() != OK)
    {
        abort();
    }
#endif

    return;
}
