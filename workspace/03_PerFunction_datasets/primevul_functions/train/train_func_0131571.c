xfs_attr_copy_value(
	struct xfs_da_args	*args,
	unsigned char		*value,
	int			valuelen)
{


	if (!args->valuelen) {
		args->valuelen = valuelen;
		return 0;
	}


	if (args->valuelen < valuelen) {
		args->valuelen = valuelen;
		return -ERANGE;
	}

	if (!args->value) {
		args->value = kmem_alloc_large(valuelen, KM_NOLOCKDEP);
		if (!args->value)
			return -ENOMEM;
	}
	args->valuelen = valuelen;


	if (args->rmtblkno)
		return xfs_attr_rmtval_get(args);


	if (!value)
		return -EINVAL;
	memcpy(args->value, value, valuelen);
	return 0;
}
