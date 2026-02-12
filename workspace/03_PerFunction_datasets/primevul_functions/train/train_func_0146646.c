flush_cursor(cursor *cr, fixed x)
{

    if (cr->first)
        return;


    if (fixed2int(cr->y) == fixed2int(cr->save_y) &&
        (cr->d == cr->save_d || cr->save_d == DIRN_UNSET)) {
        if (cr->left > cr->save_left)
            cr->left = cr->save_left;
        if (cr->right < cr->save_right)
            cr->right = cr->save_right;
        output_cursor(cr, x);
        return;
    }


    output_cursor(cr, x);
    cr->left  = cr->save_left;
    cr->right = cr->save_right;
    cr->y     = cr->save_y;
    if (cr->save_d != -1)
        cr->d = cr->save_d;
    output_cursor(cr, x);
}
