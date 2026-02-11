cdj970_print_page(gx_device_printer * pdev, FILE * prn_stream)
{
        struct error_val_field error_values;
        struct ptr_arrays data_ptrs;
        struct misc_struct misc_vars;

        Gamma gamma;

        if (cdj970->PageCtr == 0 && cdj970->ptype == DJ970C) {
                cdj970_one_time_initialisation(pdev);
        }


        memcpy(&gamma, gammat[cdj970->ptype], sizeof(Gamma));


        if (cdj970->mastergamma > 1.0) {

                do_gamma(cdj970->mastergamma, cdj970->gammavalk, gamma.k);

                do_gamma(cdj970->mastergamma, cdj970->gammavalc, gamma.c);
                do_gamma(cdj970->mastergamma, cdj970->gammavalm, gamma.m);
                do_gamma(cdj970->mastergamma, cdj970->gammavaly, gamma.y);
        }


        do_black_correction(cdj970->blackcorrect, gamma.correct);


        calculate_memory_size(pdev, &misc_vars);


        data_ptrs.storage = (ulong *) gs_malloc(pdev->memory->non_gc_memory, misc_vars.storage_size_words, W,
                                            "cdj970_print_page");


        if (data_ptrs.storage == 0) {
                return_error(gs_error_VMerror);
        }


        init_data_structure(pdev, &data_ptrs, &misc_vars);


        (*cdj970->start_raster_mode) (pdev, misc_vars.paper_size, prn_stream);


        send_scan_lines(pdev, &data_ptrs, &misc_vars, &error_values, &gamma, prn_stream);


        (*cdj970->terminate_page) (pdev, prn_stream);


        gs_free(pdev->memory->non_gc_memory, (char *)data_ptrs.storage, misc_vars.storage_size_words, W,
            "hp970_print_page");

        cdj970->PageCtr ++;

        return (0);
}
