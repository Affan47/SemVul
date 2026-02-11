r_mark_regions(struct SN_env * z) {
    z->I[0] = z->l;
    {   int c_test = z->c;
        {   int ret = z->c + 3;
            if (0 > ret || ret > z->l) return 0;
            z->c = ret;
        }
        z->I[1] = z->c;
        z->c = c_test;
    }
    if (out_grouping(z, g_v, 97, 248, 1) < 0) return 0;
    {
        int ret = in_grouping(z, g_v, 97, 248, 1);
        if (ret < 0) return 0;
        z->c += ret;
    }
    z->I[0] = z->c;

    if (!(z->I[0] < z->I[1])) goto lab0;
    z->I[0] = z->I[1];
lab0:
    return 1;
}
