scanPosixProp() {
    UnicodeSet    *uset = NULL;

    if (U_FAILURE(*fStatus)) {
        return NULL;
    }

    U_ASSERT(fC.fChar == chColon);


    int64_t     savedScanIndex        = fScanIndex;
    int64_t     savedNextIndex        = UTEXT_GETNATIVEINDEX(fRXPat->fPattern);
    UBool       savedQuoteMode        = fQuoteMode;
    UBool       savedInBackslashQuote = fInBackslashQuote;
    UBool       savedEOLComments      = fEOLComments;
    int64_t     savedLineNum          = fLineNum;
    int64_t     savedCharNum          = fCharNum;
    UChar32     savedLastChar         = fLastChar;
    UChar32     savedPeekChar         = fPeekChar;
    RegexPatternChar savedfC          = fC;


    UnicodeString propName;
    UBool         negated  = FALSE;


    nextChar(fC);
    if (fC.fChar == chUp) {
       negated = TRUE;
       nextChar(fC);
    }


    UBool  sawPropSetTerminator = FALSE;
    for (;;) {
        propName.append(fC.fChar);
        nextChar(fC);
        if (fC.fQuoted || fC.fChar == -1) {

            break;
        }
        if (fC.fChar == chColon) {
            nextChar(fC);
            if (fC.fChar == chRBracket) {
                sawPropSetTerminator = TRUE;
            }
            break;
        }
    }

    if (sawPropSetTerminator) {
        uset = createSetForProperty(propName, negated);
    }
    else
    {


        fScanIndex        = savedScanIndex;
        fQuoteMode        = savedQuoteMode;
        fInBackslashQuote = savedInBackslashQuote;
        fEOLComments      = savedEOLComments;
        fLineNum          = savedLineNum;
        fCharNum          = savedCharNum;
        fLastChar         = savedLastChar;
        fPeekChar         = savedPeekChar;
        fC                = savedfC;
        UTEXT_SETNATIVEINDEX(fRXPat->fPattern, savedNextIndex);
    }
    return uset;
}
