CL_PMpointcontents (vec3_t point)
{
	int				i, num, contents;
	entity_state_t	*ent;
	cmodel_t		*cmodel;

	contents = CM_PointContents (point, 0);

	for (i = 0; i < cl.frame.num_entities; i++)
	{
		num = (cl.frame.parse_entities + i) & PARSE_ENTITIES_MASK;
		ent = &cl_parse_entities[num];

		if (ent->solid != 31)
			continue;

		cmodel = cl.model_clip[ent->modelindex];
		if (!cmodel)
			continue;

		contents |= CM_TransformedPointContents (point, cmodel->headnode, ent->origin, ent->angles);
	}

	return contents;
}
