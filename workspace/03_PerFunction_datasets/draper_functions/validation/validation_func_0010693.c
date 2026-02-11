store_roots(radial_shading_attrs_t *rsa, const bool have_root[2], const double t[2], double r0, double r1, int point_index, bool at_corner)
{
    int i;

    for (i = 0; i < 2; i++) {
        bool good_root;

        if (!have_root[i])
            continue;
        good_root = (!rsa->have_apex || (rsa->apex <= 0 || r0 == 0 ? t[i] >= rsa->apex : t[i] <= rsa->apex));
        if (good_root) {
            radial_shading_external_contact(rsa, point_index, t[i], r0, r1, at_corner, i);
            if (!rsa->have_root[i]) {
                rsa->span[i][0] = rsa->span[i][1] = t[i];
                rsa->have_root[i] = true;
            } else {
                if (rsa->span[i][0] > t[i])
                    rsa->span[i][0] = t[i];
                if (rsa->span[i][1] < t[i])
                    rsa->span[i][1] = t[i];
            }
        }
    }
}
