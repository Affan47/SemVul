make_name_pack (PACK_T * src, PACK_T ** dst, MOID_T ** p)
{
  if (src != NO_PACK) {
    MOID_T *z;
    make_name_pack (NEXT (src), dst, p);
    z = add_mode (p, REF_SYMBOL, 0, NO_NODE, MOID (src), NO_PACK);
    (void) add_mode_to_pack (dst, z, TEXT (src), NODE (src));
  }
}
