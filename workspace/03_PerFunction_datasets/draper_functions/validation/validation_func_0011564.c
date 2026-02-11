isl_space_has_dim_name(__isl_keep isl_space *space,
	enum isl_dim_type type, unsigned pos)
{
	isl_id *id;

	if (!space)
		return -1;
	id = get_id(space, type, pos);
	return id && id->name;
}
