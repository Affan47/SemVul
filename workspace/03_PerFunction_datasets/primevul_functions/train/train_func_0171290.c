uint subselect_union_engine::cols()
{
  DBUG_ASSERT(unit->is_prepared());
  return unit->types.elements;
}
