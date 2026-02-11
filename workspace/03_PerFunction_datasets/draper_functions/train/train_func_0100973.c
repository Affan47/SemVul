varnish_delete(struct varnish *v)
{

	CHECK_OBJ_NOTNULL(v, VARNISH_MAGIC);
	vtc_logclose(v->vl);
	free(v->name);
	free(v->workdir);
	if (v->vd != NULL)
		VSM_Delete(v->vd);


	FREE_OBJ(v);
}
