_createEscXML10(const UnicodeString& ID, Transliterator::Token ) {

    return new EscapeTransliterator(ID, UnicodeString(TRUE, XML10PRE, 2), UnicodeString(SEMI[0]), 10, 1, TRUE, NULL);
}
