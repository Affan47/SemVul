multConstantGrayLow(l_uint32  *data,
                    l_int32    w,
                    l_int32    h,
                    l_int32    d,
                    l_int32    wpl,
                    l_float32  val)
{
l_int32    i, j, pval;
l_uint32   upval;
l_uint32  *line;

    for (i = 0; i < h; i++) {
        line = data + i * wpl;
        if (d == 8) {
            for (j = 0; j < w; j++) {
                pval = GET_DATA_BYTE(line, j);
                pval = (l_int32)(val * pval);
                pval = L_MIN(255, pval);
                SET_DATA_BYTE(line, j, pval);
            }
        }
        else if (d == 16) {
            for (j = 0; j < w; j++) {
                pval = GET_DATA_TWO_BYTES(line, j);
                pval = (l_int32)(val * pval);
                pval = L_MIN(0xffff, pval);
                SET_DATA_TWO_BYTES(line, j, pval);
            }
        }
        else {
            for (j = 0; j < w; j++) {
                upval = *(line + j);
                upval = (l_uint32)(val * upval);
                *(line + j) = upval;
            }
        }
    }
    return;
}
