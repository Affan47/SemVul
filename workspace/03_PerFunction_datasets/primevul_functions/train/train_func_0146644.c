gx_fill_edgebuffer_tr_app(gx_device       * pdev,
                    const gx_device_color * pdevc,
                          gx_edgebuffer   * edgebuffer,
                          int               log_op)
{
    int i, j, code;

    for (i=0; i < edgebuffer->height; ) {
        int *row    = &edgebuffer->table[edgebuffer->index[i]];
        int  rowlen = *row++;
        int *row2;
        int *rowptr;
        int *row2ptr;


        for (j = i+1; j < edgebuffer->height; j++) {
            int row2len;

            row2    = &edgebuffer->table[edgebuffer->index[j]];
            row2len = *row2++;
            row2ptr = row2;
            rowptr  = row;

            if (rowlen != row2len)
                break;
            while (row2len > 0) {
                if (rowptr[1] != row2ptr[1] || rowptr[3] != row2ptr[3])
                    goto rowdifferent;
                rowptr  += 4;
                row2ptr += 4;
                row2len--;
            }
        }
rowdifferent:{}


        while (rowlen > 0) {
            int left  = row[0];
            int right = row[2];
            row += 4;
            left = fixed2int(left);
            right = fixed2int(right + fixed_1 - 1);
            rowlen--;

            right -= left;
            if (right > 0) {
                if (log_op < 0)
                    code = dev_proc(pdev, fill_rectangle)(pdev, left, edgebuffer->base+i, right, 1, pdevc->colors.pure);
                else
                    code = gx_fill_rectangle_device_rop(left, edgebuffer->base+i, right, 1, pdevc, pdev, (gs_logical_operation_t)log_op);
                if (code < 0)
                    return code;
            }
        }


        if (i + 2 < j) {
            gs_fixed_edge le;
            gs_fixed_edge re;
            fixed ybot = int2fixed(edgebuffer->base+i+1);
            fixed ytop = int2fixed(edgebuffer->base+j-1);
            row    = &edgebuffer->table[edgebuffer->index[i]];
            rowlen = *row++;
            row2    = &edgebuffer->table[edgebuffer->index[j-1]];
            row2++;
            while (rowlen > 0) {


                le.start.x = row[0] - (fixed_half-1);
                re.start.x = row[2] + fixed_half;
                le.end.x   = row2[0] - (fixed_half-1);
                re.end.x   = row2[2] + fixed_half;
                row += 4;
                row2 += 4;
                rowlen--;

                if (le.start.x <= le.end.x) {
                    le.start.y = ybot - fixed_1 + fixed_half;
                    le.end.y   = ytop           + fixed_half;
                } else {
                    le.start.y = ybot           - fixed_half;
                    le.end.y   = ytop + fixed_1 - fixed_half;
                }

                if (re.start.x <= re.end.x) {
                    re.start.y = ybot           - fixed_half;
                    re.end.y   = ytop + fixed_1 - fixed_half;
                } else {
                    re.start.y = ybot - fixed_1 + fixed_half;
                    re.end.y   = ytop           + fixed_half;
                }

                assert(le.start.x >= -fixed_half);
                assert(le.end.x >= -fixed_half);
                assert(re.start.x >= le.start.x);
                assert(re.end.x >= le.end.x);
                assert(le.start.y <= ybot);
                assert(re.start.y <= ybot);
                assert(le.end.y >= ytop);
                assert(re.end.y >= ytop);

                code = dev_proc(pdev, fill_trapezoid)(
                                pdev,
                                &le,
                                &re,
                                ybot,
                                ytop,
                                0,
                                pdevc,
                                log_op);
                if (code < 0)
                    return code;
            }
        }

        if (i + 1 < j)
        {

            row    = &edgebuffer->table[edgebuffer->index[j-1]];
            rowlen = *row++;
            while (rowlen > 0) {
                int left  = row[0];
                int right = row[2];
                row += 4;
                left = fixed2int(left);
                right = fixed2int(right + fixed_1 - 1);
                rowlen--;

                right -= left;
                if (right > 0) {
                    if (log_op < 0)
                        code = dev_proc(pdev, fill_rectangle)(pdev, left, edgebuffer->base+j-1, right, 1, pdevc->colors.pure);
                    else
                        code = gx_fill_rectangle_device_rop(left, edgebuffer->base+j-1, right, 1, pdevc, pdev, (gs_logical_operation_t)log_op);
                    if (code < 0)
                        return code;
                }
            }
        }
        i = j;
    }
    return 0;
}
