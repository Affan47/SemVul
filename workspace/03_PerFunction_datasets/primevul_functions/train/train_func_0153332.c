static int get_parent_handle(struct device_node *np)
{
	struct device_node *parent;
	const uint32_t *prop;
	uint32_t handle;
	int len;

	parent = of_get_parent(np);
	if (!parent)

		return -ENODEV;


	prop = of_get_property(parent, "hv-handle", &len);
	if (!prop)
		prop = of_get_property(parent, "reg", &len);

	if (!prop || (len != sizeof(uint32_t))) {

		of_node_put(parent);
		return -ENODEV;
	}

	handle = be32_to_cpup(prop);
	of_node_put(parent);

	return handle;
}
