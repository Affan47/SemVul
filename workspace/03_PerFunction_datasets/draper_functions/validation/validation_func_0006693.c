memory_move_secondary_cost (enum machine_mode mode, reg_class_t rclass,
			    bool in)
{
  reg_class_t altclass;
  int partial_cost = 0;


  rtx mem ATTRIBUTE_UNUSED = top_of_stack[(int) mode];

  altclass = secondary_reload_class (in ? 1 : 0, rclass, mode, mem);

  if (altclass == NO_REGS)
    return 0;

  if (in)
    partial_cost = register_move_cost (mode, altclass, rclass);
  else
    partial_cost = register_move_cost (mode, rclass, altclass);

  if (rclass == altclass)


    return partial_cost;


  return memory_move_secondary_cost (mode, altclass, in) + partial_cost;
}
