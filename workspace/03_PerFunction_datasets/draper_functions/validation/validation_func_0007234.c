VSC_Delete(struct VSM_data *vd)
{
	struct vsc_sf *sf;
	struct vsc *vsc;

	CHECK_OBJ_NOTNULL(vd, VSM_MAGIC);
	vsc = vd->vsc;
	vd->vsc = NULL;
	CHECK_OBJ_NOTNULL(vsc, VSC_MAGIC);
	while(!VTAILQ_EMPTY(&vsc->sf_list)) {
		sf = VTAILQ_FIRST(&vsc->sf_list);
		VTAILQ_REMOVE(&vsc->sf_list, sf, next);
		free(sf->class);
		free(sf->ident);
		free(sf->name);
		FREE_OBJ(sf);
	}
}
