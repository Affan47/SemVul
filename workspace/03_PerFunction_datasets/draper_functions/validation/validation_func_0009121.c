Rd_Char_Check(WamWord start_word)
{
  WamWord word, tag_mask;
  int atom;

  DEREF(start_word, word, tag_mask);
  if (tag_mask == TAG_REF_MASK)
    Pl_Err_Instantiation();

  atom = UnTag_ATM(word);
  if (tag_mask != TAG_ATM_MASK || atom_tbl[atom].prop.length != 1)
    Pl_Err_Type(type_character, word);

  return atom_tbl[atom].name[0];
}
