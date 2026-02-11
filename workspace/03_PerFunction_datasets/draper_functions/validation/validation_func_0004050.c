finalize_hausman_test (panelmod_t *pan, PRN *prn)
{
    int mdiff = 0, err = 0;

    if (pan->bdiff != NULL && pan->Sigma != NULL) {

	mdiff = 1;
	err = bXb(pan);
    } else if (na(pan->H)) {

	err = E_DATA;
    }

    if (pan->opt & OPT_V) {
	if (!err || (mdiff && err == E_NOTPD)) {
	    print_hausman_result(pan, prn);
	}
    } else {
	if (mdiff && err == E_NOTPD) {
	    pputs(prn, _("Hausman test matrix is not positive definite"));
	    pputc(prn, '\n');
	}
	save_hausman_result(pan);
    }

    return err;
}
