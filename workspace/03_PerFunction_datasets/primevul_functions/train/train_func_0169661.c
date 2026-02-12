bool Item::eq(const Item *item, bool binary_cmp) const
{


  return type() == item->type() && name && item->name &&
    !my_strcasecmp(system_charset_info,name,item->name);
}
