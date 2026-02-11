build_predikt_table(int pos){
    int             b1, b2;
    double tt = pos_2_tt(pos);
    build_exptteig(tt);
    akt_slopes = slopes[pos] = (di_pml_matrix *) calloc(sizeof(di_pml_matrix), 1);
    akt_curves = curves[pos] = (di_pml_matrix *) calloc(sizeof(di_pml_matrix), 1);
    akt_infs = infs[pos] = (di_bool_matrix *) calloc(sizeof(di_bool_matrix), 1);

    for (b1 = 0; b1 < this->n_states; b1++) {
        for (b2 = 0; b2 <= b1; b2++) {
            p = 0.0;
            dp = 0.0;
            d2p = 0.0;
            predict(tt, b1, b2);

            if (p > 0.0){
                double ip = 1.0/p;
                akt_slopes[0][b1][b2] = dp * ip;
                akt_curves[0][b1][b2] = d2p * ip - dp * dp * (ip * ip);
                akt_infs[0][b1][b2] = 0;
                akt_slopes[0][b2][b1] = akt_slopes[0][b1][b2];
                akt_curves[0][b2][b1] = akt_curves[0][b1][b2];
                akt_infs[0][b2][b1] = 0;
            }else{
                akt_infs[0][b1][b2] = 1;
                akt_infs[0][b2][b1] = 1;
            }
        }
    }
}
