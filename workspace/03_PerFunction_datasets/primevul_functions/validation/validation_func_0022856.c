bool needs_charset_converter(uint32 length, CHARSET_INFO *tocs) const
  {


    if (!String::needs_conversion_on_storage(length,
                                             collation.collation, tocs))
      return false;


    if (collation.derivation == DERIVATION_NUMERIC &&
        collation.repertoire == MY_REPERTOIRE_ASCII &&
        !(collation.collation->state & MY_CS_NONASCII) &&
        !(tocs->state & MY_CS_NONASCII))
      return false;
    return true;
  }
