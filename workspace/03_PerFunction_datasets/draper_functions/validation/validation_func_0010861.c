print_idecode_body (lf *file, gen_entry *table, const char *result)
{
  if (table->opcode_rule->gen == switch_gen
      || table->opcode_rule->gen == goto_switch_gen
      || table->opcode_rule->gen == padded_switch_gen)
    {
      print_idecode_switch (file, table, result);
    }
  else
    {
      print_idecode_table (file, table, result);
    }
}
