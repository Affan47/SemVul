check_panel_options (gretlopt opt)
{
    if ((opt & OPT_U) && (opt & OPT_W)) {

	return E_BADOPT;
    } else if ((opt & OPT_T) && !(opt & OPT_W)) {

	return E_BADOPT;
    } else if ((opt & OPT_N) && !(opt & OPT_U)) {

	return E_BADOPT;
    } else if ((opt & OPT_C) && !(opt & OPT_P)) {

	return E_BADOPT;
    } else if (incompatible_options(opt, OPT_B | OPT_U | OPT_P)) {

	return E_BADOPT;
    }

    return 0;
}
