bool HigherMinimum(const OpDef::AttrDef& old_attr,
                   const OpDef::AttrDef& new_attr) {

  if (!new_attr.has_minimum()) return false;

  if (!old_attr.has_minimum()) return true;


  return new_attr.minimum() > old_attr.minimum();
}
