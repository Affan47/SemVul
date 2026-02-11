read_dlpoly_pbc(gint imcon, FILE *fp, struct model_pak *model)
{


    gint num_tokens, i, j;
    gchar *tokens[64];
    gchar line[1024];
    switch (imcon) {
        case 0:
            model->periodic = 0;
            return 0;
        case 1:
        case 2:
            model->periodic = 3;
            for (i=0; i < 3; ++i) {
                num_tokens = get_splitted_line(fp, 64, tokens);
                if (num_tokens < 3) {
                    gui_text_show(ERROR, "not enought numbers in PBC desc.\n");
                    return 1;
                }
                for (j=0; j<3; ++j)
                    model->latmat[3*i+j] = str_to_float(tokens[j]);
            }
            model->construct_pbc = TRUE;
            matrix_lattice_init(model);
            return 0;
        case 6:

        case 3:
        case 4:
        case 5:
        case 7:
        default:
            model->periodic = 0;

            for (i=0; i < 3; ++i)
                fgets(line, 1024, fp);
            gui_text_show(WARNING, "Sorry, not supported imcon (PBC key). "
                                   "Assuming no periodic boundaries.\n");
            return 0;
    }
}
