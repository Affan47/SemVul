void handler::adjust_next_insert_id_after_explicit_value(ulonglong nr)
{


  if ((next_insert_id > 0) && (nr >= next_insert_id))
    set_next_insert_id(compute_next_insert_id(nr, &table->in_use->variables));
}
