ortbak_(integer *nm, integer *low, integer *igh,
        doublereal *a, doublereal *ort, integer *m, doublereal *z)
{

    integer a_dim1, a_offset, z_dim1, z_offset, i_1, i_2, i_3;


    static doublereal g;
    static integer i, j, la, mm, mp, kp1, mp1;


    --ort;
    a_dim1 = *nm;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    z_dim1 = *nm;
    z_offset = z_dim1 + 1;
    z -= z_offset;


    if (*m == 0) {
        goto L200;
    }
    la = *igh - 1;
    kp1 = *low + 1;
    if (la < kp1) {
        goto L200;
    }

    i_1 = la;
    for (mm = kp1; mm <= i_1; ++mm) {
        mp = *low + *igh - mm;
        if (a[mp + (mp - 1) * a_dim1] == 0.) {
            goto L140;
        }
        mp1 = mp + 1;

        i_2 = *igh;
        for (i = mp1; i <= i_2; ++i) {

            ort[i] = a[i + (mp - 1) * a_dim1];
        }

        i_2 = *m;
        for (j = 1; j <= i_2; ++j) {
            g = 0.;

            i_3 = *igh;
            for (i = mp; i <= i_3; ++i) {

                g += ort[i] * z[i + j * z_dim1];
            }


            g = g / ort[mp] / a[mp + (mp - 1) * a_dim1];

            i_3 = *igh;
            for (i = mp; i <= i_3; ++i) {

                z[i + j * z_dim1] += g * ort[i];
            }


        }

L140:
        ;
    }

L200:
    return 0;
}
