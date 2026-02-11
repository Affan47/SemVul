xg_clear_vinsn (vliw_insn *v)
{
  int i;

  memset (v, 0, offsetof (vliw_insn, slots)
                + sizeof(TInsn) * config_max_slots);

  v->format = XTENSA_UNDEFINED;
  v->num_slots = 0;
  v->inside_bundle = FALSE;

  if (xt_saved_debug_type != DEBUG_NONE)
    debug_type = xt_saved_debug_type;

  for (i = 0; i < config_max_slots; i++)
    v->slots[i].opcode = XTENSA_UNDEFINED;
}
