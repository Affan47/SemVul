void Item_subselect::get_cache_parameters(List<Item> &parameters)
{
  Collect_deps_prm prm= {&parameters,
    unit->first_select()->nest_level_base,
    0,
    unit->first_select()->nest_level,
    TRUE
  };
  walk(&Item::collect_outer_ref_processor, TRUE, &prm);
}
