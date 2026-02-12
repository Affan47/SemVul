flush_cursor_tr(cursor_tr *cr, fixed x, int id)
{

    if (cr->first)
        return;


    if (fixed2int(cr->y) == fixed2int(cr->save_y) &&
        (cr->d == cr->save_d || cr->save_d == DIRN_UNSET)) {
        if (cr->left > cr->save_left) {
            cr->left = cr->save_left;
            cr->lid  = cr->save_lid;
        }
        if (cr->right < cr->save_right) {
            cr->right = cr->save_right;
            cr->rid = cr->save_rid;
        }
        output_cursor_tr(cr, x, id);
        return;
    }


    output_cursor_tr(cr, x, id);
    cr->left  = cr->save_left;
    cr->lid   = cr->save_lid;
    cr->right = cr->save_right;
    cr->rid   = cr->save_rid;
    cr->y     = cr->save_y;
    if (cr->save_d != -1)
        cr->d = cr->save_d;
    output_cursor_tr(cr, x, id);
}
