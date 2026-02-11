boardStatusMessage() const
{
    switch(ui.boardView->board().validate())
    {
    case Valid:
        return QString();
    case NoWhiteKing:
        return tr("No white king");
    case NoBlackKing:
        return tr("No black king");
    case DoubleCheck:
        return tr("Both kings are in check");
    case OppositeCheck:
        return tr("Side to move has opponent in check already");
    case TooManyBlackPawns:
        return tr("Black has too many pawns");
    case TooManyWhitePawns:
        return tr("White has too many pawns");
    case PawnsOn18:
        return tr("There are pawns on the first or eighth rank");
    case TooManyKings:
        return tr("Too many kings");
    case TooManyBlack:
        return tr("Too many black pieces");
    case TooManyWhite:
        return tr("Too many white pieces");
    case BadCastlingRights:
        return tr("Bad castling rights");
    case InvalidEnPassant:
        return tr("En passant square is not correct");
    default:
        return tr("Unknown reason");
    }
}
