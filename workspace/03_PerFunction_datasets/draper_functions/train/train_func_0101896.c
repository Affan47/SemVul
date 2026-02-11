shade_next_patch(shade_coord_stream_t * cs, int BitsPerFlag,
        patch_curve_t curve[4], gs_fixed_point interior[4]  )
{
    int flag = shade_next_flag(cs, BitsPerFlag);
    int num_colors, code;

    if (flag < 0) {
        if (!cs->is_eod(cs))
            return_error(gs_error_rangecheck);
        return 1;
    }
    switch (flag & 3) {
        default:
            return_error(gs_error_rangecheck);
        case 0:
            if ((code = shade_next_curve(cs, &curve[0])) < 0 ||
                (code = shade_next_coords(cs, &curve[1].vertex.p, 1)) < 0
                )
                return code;
            num_colors = 4;
            goto vx;
        case 1:
            curve[0] = curve[1], curve[1].vertex = curve[2].vertex;
            goto v3;
        case 2:
            curve[0] = curve[2], curve[1].vertex = curve[3].vertex;
            goto v3;
        case 3:
            curve[1].vertex = curve[0].vertex, curve[0] = curve[3];
v3:         num_colors = 2;
vx:         if ((code = shade_next_coords(cs, curve[1].control, 2)) < 0 ||
                (code = shade_next_curve(cs, &curve[2])) < 0 ||
                (code = shade_next_curve(cs, &curve[3])) < 0 ||
                (interior != 0 &&
                 (code = shade_next_coords(cs, interior, 4)) < 0) ||
                (code = shade_next_colors(cs, &curve[4 - num_colors],
                                          num_colors)) < 0
                )
                return code;
            cs->align(cs, 8);
    }
    return 0;
}
