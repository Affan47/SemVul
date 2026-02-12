void fix_charset_and_length_from_str_value(Derivation dv, Metadata metadata)
  {


    collation.set(str_value.charset(), dv, metadata.repertoire());
    fix_char_length(metadata.char_length());
    decimals= NOT_FIXED_DEC;
  }
