auth_grid_generate(char *username, int nrows, int ncols, int use_pin,
				   char *old_pin)
{
  int i, j;
  char *cell, *pin;
  Ds ds;
  Auth_grid *grid;

  if (ncols > 26)
	return(NULL);

  grid = auth_grid_new(NULL);
  if (old_pin != NULL)
	pin = old_pin;
  else if (use_pin) {
	ds_init(&ds);
	for (i = 0; i < pin_length; i++)
	  ds_asprintf(&ds, "%s", gen_cell());
	pin = ds_buf(&ds);
  }
  else
	pin = NULL;

  auth_grid_init(grid, username, nrows, ncols, pin);

  for (i = 0; i < nrows; i++) {
	ds_init(&ds);
	ds.clear_flag = 0;
	for (j = 0; j < ncols; j++) {
	  if ((cell = gen_cell()) == NULL)
		return(NULL);
	  ds_asprintf(&ds, "%s", cell);
	}
	dsvec_add_ptr(grid->grid, (void *) ds_buf(&ds));
  }

  return(grid);
}
