GVL_isosurf_set_att_const(int id, int isosurf_id, int att, float constant)
{
    geovol_isosurf *isosurf;

    G_debug(3, "GVL_isosurf_set_att_const() id=%d isosurf_id=%d "
	    "att=%d const=%f", id, isosurf_id, att, constant);

    isosurf = gvl_isosurf_get_isosurf(id, isosurf_id);

    if (isosurf) {
	return (gvl_isosurf_set_att_const(isosurf, att, constant));
    }

    return (-1);
}
