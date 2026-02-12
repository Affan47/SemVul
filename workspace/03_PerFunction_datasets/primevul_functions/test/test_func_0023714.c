void fix_charset_and_length(CHARSET_INFO *cs,
                              Derivation dv, Metadata metadata)
  {


    collation.set(cs, dv, metadata.repertoire());
    fix_char_length(metadata.char_length());
    decimals= NOT_FIXED_DEC;
  }
