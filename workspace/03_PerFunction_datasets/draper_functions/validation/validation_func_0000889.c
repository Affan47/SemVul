static_ok_o1 (gamgi_dlist *dlist_old,
gamgi_bool action, gamgi_window *window)
{
gamgi_cell *cell;
gamgi_dlist *dlist, *dlist_new;
gamgi_bool condition, o4;
int o1, o2, o3;
int min, max;


if (gamgi_gtk_select_entry_int (-INT_MAX,
INT_MAX, &min, &max, window) == FALSE) return NULL;


dlist_new = NULL;
for (dlist = dlist_old; dlist != NULL; dlist = dlist->next)
  {
  cell = GAMGI_CAST_CELL dlist->data;
  o1 = cell->o1;
  if (cell->origin_vectors == GAMGI_PHYS_CONVENTIONAL)
    gamgi_math_node_conventional (cell->lattice,
    cell->o1, cell->o2, cell->o3, &o1, &o2, &o3, &o4);
  condition = (o1 >= min && o1 <= max);

  if (condition != action)
    {
    dlist_new = gamgi_engine_dlist_add_start (dlist_new);
    dlist_new->data = cell;
    }
  }

return dlist_new;
}
