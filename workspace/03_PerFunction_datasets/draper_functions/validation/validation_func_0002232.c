__connman_wispr_start(struct connman_service *service,
					enum connman_ipconfig_type type)
{
	struct connman_wispr_portal_context *wp_context = NULL;
	struct connman_wispr_portal *wispr_portal = NULL;
	int index;

	DBG("service %p", service);

	if (wispr_portal_list == NULL)
		return -EINVAL;

	index = __connman_service_get_index(service);
	if (index < 0)
		return -EINVAL;

	wispr_portal = g_hash_table_lookup(wispr_portal_list,
					GINT_TO_POINTER(index));
	if (wispr_portal == NULL) {
		wispr_portal = g_try_new0(struct connman_wispr_portal, 1);
		if (wispr_portal == NULL)
			return -ENOMEM;

		g_hash_table_replace(wispr_portal_list,
					GINT_TO_POINTER(index), wispr_portal);
	}

	if (type == CONNMAN_IPCONFIG_TYPE_IPV4)
		wp_context = wispr_portal->ipv4_context;
	else if (type == CONNMAN_IPCONFIG_TYPE_IPV6)
		wp_context = wispr_portal->ipv6_context;
	else
		return -EINVAL;


	if (wp_context != NULL)
		free_connman_wispr_portal_context(wp_context);

	wp_context = create_wispr_portal_context();
	if (wp_context == NULL)
		return -ENOMEM;

	wp_context->service = service;
	wp_context->type = type;
	wp_context->wispr_portal = wispr_portal;

	if (type == CONNMAN_IPCONFIG_TYPE_IPV4)
		wispr_portal->ipv4_context = wp_context;
	else
		wispr_portal->ipv6_context = wp_context;

	return wispr_portal_detect(wp_context);
}
