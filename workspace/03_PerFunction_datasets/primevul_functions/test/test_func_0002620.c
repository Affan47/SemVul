bool MoreRestrictive(const OpDef::AttrDef& old_attr,
                     const OpDef::AttrDef& new_attr) {

  if (!new_attr.has_allowed_values()) return false;

  if (!old_attr.has_allowed_values()) return true;


  if (!IsSubsetOf(old_attr.allowed_values().list().type(),
                  new_attr.allowed_values().list().type())) {
    return true;
  }
  if (!IsSubsetOf(old_attr.allowed_values().list().s(),
                  new_attr.allowed_values().list().s())) {
    return true;
  }
  return false;
}
