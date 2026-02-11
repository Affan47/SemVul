kmo_wave_guess_table_update_2 (const char *filename,
        int ifu_nr, int global_ifu_nr,  const char *filter_id,
        int flip_trace,
        cpl_matrix **fitpars) {


    cpl_table* table = NULL;
    int selected_row = 0, i = 0;
    char *coeff_cols[NR_COEFFS_COLS] = {COEFF_COLS};
    double coeffs[NR_COEFFS_COLS];

    KMO_TRY
    {
        table = kmo_wave_guess_table_open(filename, 1);

        selected_row = kmo_wave_guess_table_get_column(table, filter_id, global_ifu_nr);

        for (i = 0; i < NR_COEFFS_COLS; i++) {
            cpl_matrix *col = cpl_matrix_extract_column(fitpars[ifu_nr-1], i);
            coeffs[i] = cpl_matrix_get_median(col);
            printf("coeffs distribution: %d %d:  %g %g %g\n", ifu_nr, i,
                    cpl_matrix_get_min(col),cpl_matrix_get_median(col),cpl_matrix_get_max(col));
        }

        if (!flip_trace) {
            double x = 2047.;
            KMO_TRY_EXIT_IF_ERROR(
                    cpl_table_set_double(table, coeff_cols[0], selected_row,
                            coeffs[0] + coeffs[1]*x + coeffs[2]*x*x + coeffs[3]*x*x*x ));
            KMO_TRY_EXIT_IF_ERROR(
                    cpl_table_set_double(table, coeff_cols[1], selected_row,
                            -coeffs[1] - 2*coeffs[2]*x - 3*coeffs[3]*x*x ));
            KMO_TRY_EXIT_IF_ERROR(
                    cpl_table_set_double(table, coeff_cols[2], selected_row,
                            coeffs[2] + 3*coeffs[3]*x ));
            KMO_TRY_EXIT_IF_ERROR(
                    cpl_table_set_double(table, coeff_cols[3], selected_row,
                            -coeffs[3]));
        } else {
            for (i = 0; i < NR_COEFFS_COLS; i++) {
                KMO_TRY_EXIT_IF_ERROR(
                        cpl_table_set_double(table, coeff_cols[i], selected_row, coeffs[i]));
            }
        }

        int dummy;
        printf("coeffs to table:                               %g %g %g %g\n",
                cpl_table_get_double(table, coeff_cols[0], selected_row, &dummy),
                cpl_table_get_double(table, coeff_cols[1], selected_row, &dummy),
                cpl_table_get_double(table, coeff_cols[2], selected_row, &dummy),
                cpl_table_get_double(table, coeff_cols[3], selected_row, &dummy)
        );

        KMO_TRY_EXIT_IF_ERROR(
                cpl_table_fill_invalid_int(table, "IFU", -1));
        KMO_TRY_EXIT_IF_ERROR(
                cpl_table_save(table, NULL, NULL, filename, CPL_IO_CREATE));

    } KMO_CATCH {
        KMO_CATCH_MSG();
    }
    cpl_table_delete(table);
}
