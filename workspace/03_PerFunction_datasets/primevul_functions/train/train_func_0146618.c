static int make_table(gx_device     * pdev,
                      gx_path       * path,
                const gs_fixed_rect * ibox,
                      int             intersection_size,
                      fixed           adjust,
                      int           * scanlinesp,
                      int          ** indexp,
                      int          ** tablep)
{
    int            scanlines;
    const subpath *psub;
    int           *index;
    int           *table;
    int            i;
    int            offset, delta;

    *scanlinesp = 0;
    *indexp     = NULL;
    *tablep     = NULL;


    scanlines = ibox->q.y-ibox->p.y;

    index     = (int *)gs_alloc_bytes(pdev->memory,
                                      (scanlines+1) * sizeof(*index),
                                      "scanc index buffer");
    if (index == NULL)
        return_error(gs_error_VMerror);


    for (i=0; i < scanlines+1; i++) {
        index[i] = 0;
    }


    for (psub = path->first_subpath; psub != 0;) {
        const segment *pseg = (const segment *)psub;
        fixed          ey = pseg->pt.y + adjust;
        fixed          iy = ey;

        while ((pseg = pseg->next) != 0 &&
               pseg->type != s_start
            ) {
            fixed sy = ey;
            ey = pseg->pt.y + adjust;

#ifdef DEBUG_SCAN_CONVERTER
            dlprintf1("%d ", pseg->type);
#endif
            switch (pseg->type) {
                default:
                case s_start:
                case s_dash:
                    assert("This should never happen" == NULL);
                    break;
                case s_curve: {
                    const curve_segment *const pcur = (const curve_segment *)pseg;
                    fixed c1y = pcur->p1.y + adjust;
                    fixed c2y = pcur->p2.y + adjust;
                    fixed maxy = sy, miny = sy;
                    int imaxy, iminy;
                    if (miny > c1y)
                        miny = c1y;
                    if (miny > c2y)
                        miny = c2y;
                    if (miny > ey)
                        miny = ey;
                    if (maxy < c1y)
                        maxy = c1y;
                    if (maxy < c2y)
                        maxy = c2y;
                    if (maxy < ey)
                        maxy = ey;
                    iminy = fixed2int(miny) - ibox->p.y;
                    if (iminy < 0)
                        iminy = 0;
                    if (iminy < scanlines) {
                        imaxy = fixed2int(maxy) - ibox->p.y;
                        if (imaxy >= 0) {
                            index[iminy]+=3;
                            if (imaxy < scanlines)
                                index[imaxy+1]-=3;
                        }
                    }
                    break;
                }
                case s_gap:
                case s_line:
                case s_line_close: {
                    fixed miny, maxy;
                    int imaxy, iminy;
                    if (sy == ey)
                        break;
                    if (sy < ey)
                        miny = sy, maxy = ey;
                    else
                        miny = ey, maxy = sy;
                    iminy = fixed2int(miny) - ibox->p.y;
                    if (iminy < 0)
                        iminy = 0;
                    if (iminy < scanlines) {
                        imaxy = fixed2int(maxy) - ibox->p.y;
                        if (imaxy >= 0) {
                            index[iminy]++;
                            if (imaxy < scanlines) {
                                index[imaxy+1]--;
                            }
                        }
                    }
                    break;
                }
            }


            if (ey != iy) {
                fixed miny, maxy;
                int imaxy, iminy;
                if (iy < ey)
                    miny = iy, maxy = ey;
                else
                    miny = ey, maxy = iy;
                iminy = fixed2int(miny) - ibox->p.y;
                if (iminy < 0)
                    iminy = 0;
                if (iminy < scanlines) {
                    imaxy = fixed2int(maxy) - ibox->p.y;
                    if (imaxy >= 0) {
                        index[iminy]++;
                        if (imaxy < scanlines) {
                            index[imaxy+1]--;
                        }
                    }
                }
            }
        }
#ifdef DEBUG_SCAN_CONVERTER
        dlprintf("\n");
#endif
        psub = (const subpath *)pseg;
    }


    offset = 0;
    delta  = 0;
    for (i=0; i < scanlines; i++) {
        delta    += intersection_size*index[i];
        index[i]  = offset;
        offset   += delta+1;
    }


    table = (int *)gs_alloc_bytes(pdev->memory, offset * sizeof(*table),
                                  "scanc intersects buffer");
    if (table == NULL) {
        gs_free_object(pdev->memory, table, "scanc index buffer");
        return_error(gs_error_VMerror);
    }


    for (i=0; i < scanlines; i++) {
        table[index[i]] = 0;
    }

    *scanlinesp = scanlines;
    *tablep     = table;
    *indexp     = index;

    return 0;
}
