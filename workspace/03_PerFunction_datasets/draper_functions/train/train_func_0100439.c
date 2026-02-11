client_delete(struct client *c)
{

	CHECK_OBJ_NOTNULL(c, CLIENT_MAGIC);
	vtc_logclose(c->vl);
	free(c->spec);
	free(c->name);

	FREE_OBJ(c);
}
