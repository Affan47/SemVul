StringPiece Formattable::getDecimalNumber(UErrorCode &status) {
    if (U_FAILURE(status)) {
        return "";
    }
    if (fDecimalStr != NULL) {
      return fDecimalStr->toStringPiece();
    }

    CharString *decimalStr = internalGetCharString(status);
    if(decimalStr == NULL) {
      return "";
    } else {
      return decimalStr->toStringPiece();
    }
}
