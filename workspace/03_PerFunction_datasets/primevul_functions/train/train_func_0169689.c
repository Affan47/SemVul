Item *Item_int_with_ref::clone_item()
{
  DBUG_ASSERT(ref->const_item());


  return (ref->unsigned_flag ?
          new Item_uint(ref->name, ref->val_int(), ref->max_length) :
          new Item_int(ref->name, ref->val_int(), ref->max_length));
}
