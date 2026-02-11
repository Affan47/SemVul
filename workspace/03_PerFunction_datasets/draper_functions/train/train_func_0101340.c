deps_init_id (idata_t id, insn_t insn, bool force_unique_p)
{
  struct deps_desc _dc, *dc = &_dc;

  deps_init_id_data.where = DEPS_IN_NOWHERE;
  deps_init_id_data.id = id;
  deps_init_id_data.force_unique_p = force_unique_p;
  deps_init_id_data.force_use_p = false;

  init_deps (dc, false);

  memcpy (&deps_init_id_sched_deps_info,
	  &const_deps_init_id_sched_deps_info,
	  sizeof (deps_init_id_sched_deps_info));

  if (spec_info != NULL)
    deps_init_id_sched_deps_info.generate_spec_deps = 1;

  sched_deps_info = &deps_init_id_sched_deps_info;

  deps_analyze_insn (dc, insn);

  free_deps (dc);

  deps_init_id_data.id = NULL;
}
