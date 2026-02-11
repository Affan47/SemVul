resources_available (resource_table *rt, xtensa_opcode opcode, int cycle)
{
  int i;
  int uses = (rt->opcode_num_units) (rt->data, opcode);

  for (i = 0; i < uses; i++)
    {
      xtensa_funcUnit unit = (rt->opcode_unit_use) (rt->data, opcode, i);
      int stage = (rt->opcode_unit_stage) (rt->data, opcode, i);
      int copies_in_use = rt->units[stage + cycle][unit];
      int copies = (rt->unit_num_copies) (rt->data, unit);
      if (copies_in_use >= copies)
	return FALSE;
    }
  return TRUE;
}
