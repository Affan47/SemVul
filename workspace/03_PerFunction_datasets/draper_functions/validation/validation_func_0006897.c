t1_hinter__is_inside(t1_hinter * self, t1_glyph_space_coord gx, t1_glyph_space_coord gy, int c)
{
    int b = self->contour[c];
    int e = self->contour[c + 1] - 1;
    double a = 0, A;
    int i;

    for (i = b; i < e;) {
        if (self->pole[i + 1].type != offcurve) {
            A = bar_winding_angle(self->pole[i + 0].gx - gx, self->pole[i + 0].gy - gy,
                                    self->pole[i + 1].gx - gx, self->pole[i + 1].gy - gy);
            i++;
        } else {
            A = curve_winding_angle(self->pole[i + 0].gx - gx, self->pole[i + 0].gy - gy,
                                    self->pole[i + 1].gx - gx, self->pole[i + 1].gy - gy,
                                    self->pole[i + 2].gx - gx, self->pole[i + 2].gy - gy,
                                    self->pole[i + 3].gx - gx, self->pole[i + 3].gy - gy);
            i += 3;
        }
        if (A == CONTACT_SIGNAL)
            return -1;
        a += A;
    }
    if (any_abs(a) < 0.1)
        return 0;
    return 1;
}
