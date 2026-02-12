DecimalQuantity &DecimalQuantity::setToDecNumber(StringPiece n, UErrorCode& status) {
    setBcdToZero();
    flags = 0;


    DecNum decnum;
    decnum.setTo(n, status);

    _setToDecNum(decnum, status);
    return *this;
}
