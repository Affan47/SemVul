mapdeco_add_gotoline(const struct tile *ptile, enum direction8 dir)
{
  struct gotoline_counter *pglc;
  const struct tile *ptile_dest;
  bool changed;

  if (!mapdeco_gotoline_table || !ptile
      || !(0 <= dir && dir <= direction8_max())) {
    return;
  }
  ptile_dest = mapstep(ptile, dir);
  if (!ptile_dest) {
    return;
  }

  if (!gotoline_hash_lookup(mapdeco_gotoline_table, ptile, &pglc)) {
    pglc = gotoline_counter_new();
    gotoline_hash_insert(mapdeco_gotoline_table, ptile, pglc);
  }
  changed = (pglc->line_count[dir] < 1);
  pglc->line_count[dir]++;

  if (changed) {

    refresh_tile_mapcanvas((struct tile *) ptile, FALSE, FALSE);
    refresh_tile_mapcanvas((struct tile *) ptile_dest, FALSE, FALSE);
  }
}
