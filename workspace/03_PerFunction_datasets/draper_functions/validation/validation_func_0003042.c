make_tex_coeff_name (const MODEL *pmod, const DATASET *dset, int i,
			  char *name)
{
    char pname[VNAMELEN];

    gretl_model_get_param_name(pmod, dset, i, pname);

    if (pmod->aux == AUX_ARCH) {
	tex_make_cname(name, pname);
    } else if (pmod->ci == NLS) {
	if (!tex_greek_param(name, pname)) {
	    tex_escape(name, pname);
	}
    } else if (pmod->ci == ARMA) {
	tex_arma_coeff_name(name, pname, 0);
    } else if (pmod->ci == GARCH) {
	tex_garch_coeff_name(name, pname, 0);
    } else if (pmod->ci == VAR) {
	tex_VAR_varname(name, pmod, dset, i);
    } else if (pmod->aux == AUX_VECM) {
	tex_VECM_varname(name, pmod, dset, i);
    } else if (pmod->ci == MPOLS) {
	tex_mp_coeff_name(name, pname, 0);
    } else {
	tex_escape(name, pname);
    }
}
