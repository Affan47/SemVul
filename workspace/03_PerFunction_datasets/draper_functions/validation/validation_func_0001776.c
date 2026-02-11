caml_final_register (value f, value v)
{
  if (!(Is_block (v) && Is_in_heap_or_young(v))) {
    caml_invalid_argument ("Gc.finalise");
  }
  Assert (old <= young);

  if (young >= size){
    if (final_table == NULL){
      uintnat new_size = 30;
      final_table = caml_stat_alloc (new_size * sizeof (struct final));
      Assert (old == 0);
      Assert (young == 0);
      size = new_size;
    }else{
      uintnat new_size = size * 2;
      final_table = caml_stat_resize (final_table,
                                      new_size * sizeof (struct final));
      size = new_size;
    }
  }
  Assert (young < size);
  final_table[young].fun = f;
  if (Tag_val (v) == Infix_tag){
    final_table[young].offset = Infix_offset_val (v);
    final_table[young].val = v - Infix_offset_val (v);
  }else{
    final_table[young].offset = 0;
    final_table[young].val = v;
  }
  ++ young;

  return Val_unit;
}
