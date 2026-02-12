int gx_scan_convert(gx_device     * pdev,
                    gx_path       * path,
              const gs_fixed_rect * clip,
                    gx_edgebuffer * edgebuffer,
                    fixed           fixed_flat)
{
    gs_fixed_rect  ibox;
    int            scanlines;
    const subpath *psub;
    int           *index;
    int           *table;
    int            i;
    int            code;

    edgebuffer->index = NULL;
    edgebuffer->table = NULL;


    if (path->first_subpath == NULL)
        return 0;

    code = make_bbox(path, clip, &ibox, fixed_half);
    if (code < 0)
        return code;

    if (ibox.q.y <= ibox.p.y)
        return 0;

    code = make_table(pdev, path, &ibox, 1, fixed_half, &scanlines, &index, &table);
    if (code < 0)
        return code;


    for (psub = path->first_subpath; psub != 0;) {
        const segment *pseg = (const segment *)psub;
        fixed ex = pseg->pt.x;
        fixed ey = pseg->pt.y;
        fixed ix = ex;
        fixed iy = ey;

        while ((pseg = pseg->next) != 0 &&
               pseg->type != s_start
            ) {
            fixed sx = ex;
            fixed sy = ey;
            ex = pseg->pt.x;
            ey = pseg->pt.y;

            switch (pseg->type) {
                default:
                case s_start:
                case s_dash:
                    assert("This should never happen" == NULL);
                    break;
                case s_curve: {
                    const curve_segment *const pcur = (const curve_segment *)pseg;
                    int k = gx_curve_log2_samples(sx, sy, pcur, fixed_flat);

                    mark_curve(sx, sy, pcur->p1.x, pcur->p1.y, pcur->p2.x, pcur->p2.y, ex, ey, ibox.p.y, scanlines, table, index, k);
                    break;
                }
                case s_gap:
                case s_line:
                case s_line_close:
                    if (sy != ey)
                        mark_line(sx, sy, ex, ey, ibox.p.y, scanlines, table, index);
                    break;
            }
        }

        if (iy != ey)
            mark_line(ex, ey, ix, iy, ibox.p.y, scanlines, table, index);
        psub = (const subpath *)pseg;
    }


    for (i=0; i < scanlines; i++) {
        int *row = &table[index[i]];
        int  rowlen = *row++;


        qsort(row, rowlen, sizeof(int), intcmp);
    }

    edgebuffer->base   = ibox.p.y;
    edgebuffer->height = scanlines;
    edgebuffer->xmin   = ibox.p.x;
    edgebuffer->xmax   = ibox.q.x;
    edgebuffer->index  = index;
    edgebuffer->table  = table;

    return 0;
}
