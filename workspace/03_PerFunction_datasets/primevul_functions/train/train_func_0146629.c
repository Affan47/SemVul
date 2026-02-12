static void mark_line_tr_app(cursor_tr *cr, fixed sx, fixed sy, fixed ex, fixed ey, int id)
{
    int isy = fixed2int(sy) - cr->base;
    int iey = fixed2int(ey) - cr->base;

    if (sx == ex && sy == ey)
        return;
#ifdef DEBUG_SCAN_CONVERTER
    dlprintf6("Marking line from %x,%x to %x,%x (%x,%x)\n", sx, sy, ex, ey, isy, iey);
#endif

    assert(cr->y == sy && cr->left <= sx && cr->right >= sx && cr->d >= DIRN_UNSET && cr->d <= DIRN_DOWN);


    if (isy == iey) {
        if (sy == ey) {

        } else if (sy > ey) {

            if (cr->d == DIRN_UP)
                output_cursor_tr(cr, sx, id);
            cr->d = DIRN_DOWN;
        } else {

            if (cr->d == DIRN_DOWN)
                output_cursor_tr(cr, sx, id);
            cr->d = DIRN_UP;
        }
        if (sx <= ex) {
            if (sx < cr->left) {
                cr->left = sx;
                cr->lid  = id;
            }
            if (ex > cr->right) {
                cr->right = ex;
                cr->rid   = id;
            }
        } else {
            if (ex < cr->left) {
                cr->left = ex;
                cr->lid  = id;
            }
            if (sx > cr->right) {
                cr->right = sx;
                cr->rid   = id;
            }
        }
        cr->y = ey;
    } else if (sy < ey) {

        fixed y_steps = ey - sy;


        int phase1_y_steps = (fixed_1 - sy) & (fixed_1 - 1);
        int phase3_y_steps = ey & (fixed_1 - 1);

        if (cr->d == DIRN_DOWN)
            output_cursor_tr(cr, sx, id);
        cr->d = DIRN_UP;

        if (sx <= ex) {

            int phase1_x_steps, phase3_x_steps;
            fixed x_steps = ex - sx;

            assert(cr->left <= sx);

            if (phase1_y_steps) {
                phase1_x_steps = (int)(((int64_t)x_steps * phase1_y_steps + y_steps/2) / y_steps);
                sx += phase1_x_steps;
                if (cr->right <= sx) {
                    cr->right = sx;
                    cr->rid   = id;
                }
                x_steps -= phase1_x_steps;


                if (fixed2int(cr->y) != fixed2int(cr->y + phase1_y_steps))
                    output_cursor_tr(cr, sx, id);
                cr->y += phase1_y_steps;
                sy += phase1_y_steps;
                y_steps -= phase1_y_steps;
                if (y_steps == 0)
                    return;
            }


            phase3_x_steps = (int)(((int64_t)x_steps * phase3_y_steps + y_steps/2) / y_steps);
            x_steps -= phase3_x_steps;
            y_steps -= phase3_y_steps;


            cr->lid = id;
            cr->rid = id;
            y_steps = fixed2int(y_steps);
            assert(y_steps >= 0);
            if (y_steps) {


                int x_inc = x_steps/y_steps;
                int n_inc = x_steps - (x_inc * y_steps);
                int f = y_steps/2;
                int d = y_steps;
                while (y_steps) {
                    cr->left = sx;
                    sx += x_inc;
                    f -= n_inc;
                    if (f < 0)
                        f += d, sx++;
                    cr->right = sx;
                    y_steps--;
                    output_cursor_tr(cr, sx, id);
                    cr->y += fixed_1;
                }
            }


            cr->left  = sx;
            cr->right = ex;
            cr->y += phase3_y_steps;
        } else {

            int phase1_x_steps, phase3_x_steps;
            fixed x_steps = sx - ex;

            assert(cr->right >= sx);

            if (phase1_y_steps) {
                phase1_x_steps = (int)(((int64_t)x_steps * phase1_y_steps + y_steps/2) / y_steps);
                sx -= phase1_x_steps;
                if (cr->left > sx) {
                    cr->left = sx;
                    cr->lid  = id;
                }
                x_steps -= phase1_x_steps;


                if (fixed2int(cr->y) != fixed2int(cr->y + phase1_y_steps))
                    output_cursor_tr(cr, sx, id);
                cr->y += phase1_y_steps;
                sy += phase1_y_steps;
                y_steps -= phase1_y_steps;
                if (y_steps == 0)
                    return;
            }


            phase3_x_steps = (int)(((int64_t)x_steps * phase3_y_steps + y_steps/2) / y_steps);
            x_steps -= phase3_x_steps;
            y_steps -= phase3_y_steps;


            cr->lid = id;
            cr->rid = id;
            assert((y_steps & (fixed_1 - 1)) == 0);
            y_steps = fixed2int(y_steps);
            assert(y_steps >= 0);
            if (y_steps) {


                int x_inc = x_steps/y_steps;
                int n_inc = x_steps - (x_inc * y_steps);
                int f = y_steps/2;
                int d = y_steps;
                while (y_steps) {
                    cr->right = sx;
                    sx -= x_inc;
                    f -= n_inc;
                    if (f < 0)
                        f += d, sx--;
                    cr->left = sx;
                    y_steps--;
                    output_cursor_tr(cr, sx, id);
                    cr->y += fixed_1;
                }
            }


            cr->right = sx;
            cr->left  = ex;
            cr->y += phase3_y_steps;
        }
    } else {

        fixed y_steps = sy - ey;


        int phase1_y_steps = sy & (fixed_1 - 1);
        int phase3_y_steps = (fixed_1 - ey) & (fixed_1 - 1);

        if (cr->d == DIRN_UP)
            output_cursor_tr(cr, sx, id);
        cr->d = DIRN_DOWN;

        if (sx <= ex) {

            int phase1_x_steps, phase3_x_steps;
            fixed x_steps = ex - sx;


            assert(cr->left <= sx);
            if (phase1_y_steps) {
                phase1_x_steps = (int)(((int64_t)x_steps * phase1_y_steps + y_steps/2) / y_steps);
                sx += phase1_x_steps;
                if (cr->right < sx) {
                    cr->right = sx;
                    cr->rid   = id;
                }
                x_steps -= phase1_x_steps;

                sy -= phase1_y_steps;
                cr->y -= phase1_y_steps;
                y_steps -= phase1_y_steps;
                if (y_steps == 0)
                    return;
            }


            phase3_x_steps = (int)(((int64_t)x_steps * phase3_y_steps + y_steps/2) / y_steps);
            x_steps -= phase3_x_steps;
            y_steps -= phase3_y_steps;


            assert((y_steps & (fixed_1 - 1)) == 0);
            y_steps = fixed2int(y_steps);
            assert(y_steps >= 0);
            if (y_steps) {


                int x_inc = x_steps/y_steps;
                int n_inc = x_steps - (x_inc * y_steps);
                int f = y_steps/2;
                int d = y_steps;
                while (y_steps) {
                    output_cursor_tr(cr, sx, id);
                    sx += x_inc;
                    f -= n_inc;
                    if (f < 0)
                        f += d, sx++;
                    cr->right = sx;
                    y_steps--;
                    cr->y -= fixed_1;
                }
            }


            if (phase3_y_steps > 0)
                output_cursor_tr(cr, sx, id);
            cr->left  = sx;
            cr->right = ex;
            cr->y -= phase3_y_steps;
        } else {

            int phase1_x_steps, phase3_x_steps;
            fixed x_steps = sx - ex;


            assert(cr->right >= sx);
            if (phase1_y_steps) {
                phase1_x_steps = (int)(((int64_t)x_steps * phase1_y_steps + y_steps/2) / y_steps);
                sx -= phase1_x_steps;
                if (cr->left > sx) {
                    cr->left = sx;
                    cr->lid  = id;
                }
                x_steps -= phase1_x_steps;

                sy -= phase1_y_steps;
                cr->y -= phase1_y_steps;
                y_steps -= phase1_y_steps;
                if (y_steps == 0)
                    return;
            }


            phase3_x_steps = (int)(((int64_t)x_steps * phase3_y_steps + y_steps/2) / y_steps);
            x_steps -= phase3_x_steps;
            y_steps -= phase3_y_steps;


            y_steps = fixed2int(y_steps);
            assert(y_steps >= 0);
            if (y_steps) {


                int x_inc = x_steps/y_steps;
                int n_inc = x_steps - (x_inc * y_steps);
                int f = y_steps/2;
                int d = y_steps;
                while (y_steps) {
                    output_cursor_tr(cr, sx, id);
                    sx -= x_inc;
                    f -= n_inc;
                    if (f < 0)
                        f += d, sx--;
                    cr->left = sx;
                    y_steps--;
                    cr->y -= fixed_1;
                }
            }


            if (phase3_y_steps > 0)
                output_cursor_tr(cr, sx, id);
            cr->right = sx;
            cr->left  = ex;
            cr->y -= phase3_y_steps;
        }
    }
}
