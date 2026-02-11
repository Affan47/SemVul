key_type() const
{
  enum ha_base_keytype res;

  if (binary())
    res= length_bytes == 1 ? HA_KEYTYPE_VARBINARY1 : HA_KEYTYPE_VARBINARY2;
  else
    res= length_bytes == 1 ? HA_KEYTYPE_VARTEXT1 : HA_KEYTYPE_VARTEXT2;
  return res;
}
