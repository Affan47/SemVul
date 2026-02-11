git_object__from_odb_object(
	git_object **object_out,
	git_repository *repo,
	git_odb_object *odb_obj,
	git_otype type)
{
	int error;
	git_object *object = NULL;

	if (type != GIT_OBJ_ANY && type != odb_obj->raw.type) {
		giterr_set(GITERR_ODB, "The requested type does not match the type in the ODB");
		return GIT_ENOTFOUND;
	}

	type = odb_obj->raw.type;

	if ((error = create_object(&object, type)) < 0)
		return error;


	git_oid_cpy(&object->cached.oid, &odb_obj->cached.oid);
	object->repo = repo;

	switch (type) {
	case GIT_OBJ_COMMIT:
		error = git_commit__parse((git_commit *)object, odb_obj);
		break;

	case GIT_OBJ_TREE:
		error = git_tree__parse((git_tree *)object, odb_obj);
		break;

	case GIT_OBJ_TAG:
		error = git_tag__parse((git_tag *)object, odb_obj);
		break;

	case GIT_OBJ_BLOB:
		error = git_blob__parse((git_blob *)object, odb_obj);
		break;

	default:
		break;
	}

	if (error < 0)
		git_object__free(object);
	else
		*object_out = git_cache_try_store(&repo->objects, object);

	return error;
}
