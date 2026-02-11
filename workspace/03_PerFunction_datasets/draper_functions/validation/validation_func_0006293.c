get_pair1(chasen_cell_t * cell, rensetu_pair_t * pair)
{
    chasen_cell_t *cell_p;

    pair->hinsi = 0;
    pair->type = 0;
    pair->form = 0;
    pair->goi = NULL;

    if (nullp(cell_p = cha_car(cell)))
	return;
    pair->hinsi = cha_get_nhinsi_id(cell_p);

    if (nullp(cell_p = cha_car(cell = cha_cdr(cell))))
	return;
    pair->type = cha_get_type_id(cha_s_atom(cell_p));

    if (nullp(cell_p = cha_car(cell = cha_cdr(cell))))
	return;
    pair->form = cha_get_form_id(cha_s_atom(cell_p), pair->type);

    if (nullp(cell_p = cha_car(cell = cha_cdr(cell))))
	return;
    pair->goi = cha_strdup(cha_s_atom(cell_p));
}
