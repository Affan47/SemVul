foreign_execute (const DATASET *dset,
		     gretlopt opt, PRN *prn)
{
    int i, err = 0;

    if (foreign_lang == LANG_R) {
	make_gretl_R_names();
    }

    if (opt & OPT_V) {

	for (i=0; i<foreign_n_lines; i++) {
	    pprintf(prn, "> %s\n", foreign_lines[i]);
	}
    }

    foreign_opt |= opt;

    if (foreign_lang == LANG_R) {
#ifdef USE_RLIB
	if (gretl_use_Rlib()) {
	    err = run_R_lib(dset, foreign_opt, prn);
	} else {
	    err = run_R_binary(dset, foreign_opt, prn);
	}
#else
	err = run_R_binary(dset, foreign_opt, prn);
#endif
    } else if (foreign_lang == LANG_OX) {
	err = write_gretl_ox_file(NULL, foreign_opt, NULL);
	if (err) {
	    delete_gretl_ox_file();
	} else {
	    err = lib_run_other_sync(foreign_opt, prn);
	}
    } else if (foreign_lang == LANG_OCTAVE) {
	err = write_gretl_octave_file(NULL, foreign_opt,
				      dset, NULL);
	if (err) {
	    delete_gretl_octave_file();
	} else {
	    err = lib_run_other_sync(foreign_opt, prn);
	}
    } else if (foreign_lang == LANG_STATA) {
	err = write_gretl_stata_file(NULL, foreign_opt,
				     dset, NULL);
	if (err) {
	    delete_gretl_stata_file();
	} else {
	    err = lib_run_other_sync(foreign_opt, prn);
	}
    } else if (foreign_lang == LANG_PYTHON) {
	err = write_gretl_python_file(NULL, foreign_opt,
				      NULL);
	if (err) {
	    delete_gretl_python_file();
	} else {
	    err = lib_run_other_sync(foreign_opt, prn);
	}
    } else {

	err = E_DATA;
    }

    destroy_foreign();

    return err;
}
