output_cursor_tr(cursor_tr *cr, fixed x, int id)
{
    int iy = fixed2int(cr->y) - cr->base;
    int *row;
    int count;

    if (iy < 0 || iy >= cr->scanlines) {

    }
    else if (cr->first) {

        cr->save_left  = cr->left;
        cr->save_lid   = cr->lid;
        cr->save_right = cr->right;
        cr->save_rid   = cr->rid;
        cr->save_y     = cr->y;
        cr->save_d     = cr->d;
        cr->first      = 0;
    } else {

        assert(cr->d != DIRN_UNSET);

        row = &cr->table[cr->index[iy]];
        *row = count = (*row)+1;
        row[4 * count - 3] = cr->left;
        row[4 * count - 2] = cr->d | (cr->lid<<1);
        row[4 * count - 1] = cr->right;
        row[4 * count    ] = cr->rid;
    }
    cr->left  = x;
    cr->lid   = id;
    cr->right = x;
    cr->rid   = id;
}
