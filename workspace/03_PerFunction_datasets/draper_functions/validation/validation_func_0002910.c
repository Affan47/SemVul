add_mode (MOID_T ** z, int att, int dim, NODE_T * node, MOID_T * sub, PACK_T * pack)
{
  MOID_T *new_mode = new_moid ();
  ABEND (att == REF_SYMBOL && sub == NO_MOID, ERROR_INTERNAL_CONSISTENCY, "store REF NULL");
  ABEND (att == FLEX_SYMBOL && sub == NO_MOID, ERROR_INTERNAL_CONSISTENCY, "store FLEX NULL");
  ABEND (att == ROW_SYMBOL && sub == NO_MOID, ERROR_INTERNAL_CONSISTENCY, "store [] NULL");
  USE (new_mode) = A68_FALSE;
  SIZE (new_mode) = 0;
  ATTRIBUTE (new_mode) = att;
  DIM (new_mode) = dim;
  NODE (new_mode) = node;
  HAS_ROWS (new_mode) = (BOOL_T) (att == ROW_SYMBOL);
  SUB (new_mode) = sub;
  PACK (new_mode) = pack;
  NEXT (new_mode) = NO_MOID;
  EQUIVALENT (new_mode) = NO_MOID;
  SLICE (new_mode) = NO_MOID;
  DEFLEXED (new_mode) = NO_MOID;
  NAME (new_mode) = NO_MOID;
  MULTIPLE (new_mode) = NO_MOID;
  ROWED (new_mode) = NO_MOID;
  return (register_extra_mode (z, new_mode));
}
