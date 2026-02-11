AP_conservProfile2Gnuplot_callback(AW_window *aww) {
    GB_ERROR  error   = 0;
    char     *command_file;
    char     *cmdName = GB_unique_filename("arb", "gnuplot");
    FILE     *cmdFile = GB_fopen_tempfile(cmdName, "wt", &command_file);

    if (!cmdFile) error = GB_await_error();
    else {
        char *fname   = aww->get_root()->awar(AP_AWAR_CONSPRO_FILENAME)->read_string();
        char *smooth  = aww->get_root()->awar(AP_AWAR_CONSPRO_SMOOTH_GNUPLOT)->read_string();
        char *legend  = aww->get_root()->awar(AP_AWAR_CONSPRO_GNUPLOT_LEGEND)->read_string();
        int   dispPos = aww->get_root()->awar(AP_AWAR_CONSPRO_GNUPLOT_DISP_POS)->read_int();
        int   minX    = aww->get_root()->awar(AP_AWAR_CONSPRO_GNUPLOT_MIN_X)->read_int();
        int   maxX    = aww->get_root()->awar(AP_AWAR_CONSPRO_GNUPLOT_MAX_X)->read_int();
        int   minY    = aww->get_root()->awar(AP_AWAR_CONSPRO_GNUPLOT_MIN_Y)->read_int();
        int   maxY    = aww->get_root()->awar(AP_AWAR_CONSPRO_GNUPLOT_MAX_Y)->read_int();

        if (minX>0 || maxX>0)   fprintf(cmdFile, "set xrange [%i:%i]\n",minX,maxX);
        if (minY>0 || maxY>0)   fprintf(cmdFile, "set yrange [%i:%i]\n",minY,maxY);

        fprintf(cmdFile, "plot \"%s\" %s title \"%s\"\n", fname, smooth, legend);

        if(dispPos)  fprintf(cmdFile, "replot \"%s\" title \"Base Positions\"\n", fname);

        fprintf(cmdFile, "pause -1 \"Press RETURN to close gnuplot\"\n");

        free(legend);
        free(smooth);
        free(fname);
    }
    fclose(cmdFile);

    if (!error) {
        char *script = GBS_global_string_copy("gnuplot %s && rm -f %s", command_file, command_file);
        GB_xcmd(script, GB_TRUE, GB_TRUE);
        free(script);
    }
    free(command_file);
    free(cmdName);

    if (error) aw_message(error);
}
