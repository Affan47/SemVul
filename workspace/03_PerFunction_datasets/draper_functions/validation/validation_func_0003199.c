add_part(struct goto_map *goto_map)
{
  struct part *p;
  struct pf_parameter parameter = goto_map->template;
  struct unit *punit = goto_map->focus;

  if (!punit) {
    return;
  }

  goto_map->num_parts++;
  goto_map->parts =
      fc_realloc(goto_map->parts,
                 goto_map->num_parts * sizeof(*goto_map->parts));
  p = &goto_map->parts[goto_map->num_parts - 1];

  if (goto_map->num_parts == 1) {

    p->start_tile = unit_tile(punit);
    p->start_moves_left = parameter.moves_left_initially;
    p->start_fuel_left = parameter.fuel_left_initially;
  } else {
    struct part *prev = &goto_map->parts[goto_map->num_parts - 2];

    p->start_tile = prev->end_tile;
    p->start_moves_left = prev->end_moves_left;
    p->start_fuel_left = prev->end_fuel_left;
    parameter.moves_left_initially = p->start_moves_left;
    parameter.fuel_left_initially = p->start_fuel_left;
  }
  p->path = NULL;
  p->end_tile = p->start_tile;
  p->mp = 0;
  parameter.start_tile = p->start_tile;
  p->map = pf_map_new(&parameter);
}
