static WERROR dnsserver_enumerate_records(struct dnsserver_state *dsstate,
					TALLOC_CTX *mem_ctx,
					struct dnsserver_zone *z,
					unsigned int client_version,
					const char *node_name,
					const char *start_child,
					enum dns_record_type record_type,
					unsigned int select_flag,
					const char *filter_start,
					const char *filter_stop,
					unsigned int *buffer_length,
					struct DNS_RPC_RECORDS_ARRAY **buffer)
{
	TALLOC_CTX *tmp_ctx;
	char *name;
	const char * const attrs[] = { "name", "dnsRecord", NULL };
	struct ldb_result *res = NULL;
	struct DNS_RPC_RECORDS_ARRAY *recs = NULL;
	char **add_names = NULL;
	char *rname = NULL;
	const char *preference_name = NULL;
	int add_count = 0;
	int i, ret, len;
	WERROR status;
	struct dns_tree *tree = NULL;
	struct dns_tree *base = NULL;
	struct dns_tree *node = NULL;

	tmp_ctx = talloc_new(mem_ctx);
	W_ERROR_HAVE_NO_MEMORY(tmp_ctx);

	name = dns_split_node_name(tmp_ctx, node_name, z->name);
	W_ERROR_HAVE_NO_MEMORY_AND_FREE(name, tmp_ctx);


	if (strcasecmp(name, z->name) == 0) {
		ret = ldb_search(dsstate->samdb, tmp_ctx, &res, z->zone_dn,
				 LDB_SCOPE_ONELEVEL, attrs,
				 "(&(objectClass=dnsNode)(!(dNSTombstoned=TRUE)))");
		preference_name = "@";
	} else {
		char *encoded_name
			= ldb_binary_encode_string(tmp_ctx, name);
		ret = ldb_search(dsstate->samdb, tmp_ctx, &res, z->zone_dn,
				 LDB_SCOPE_ONELEVEL, attrs,
				 "(&(objectClass=dnsNode)(|(name=%s)(name=*.%s))(!(dNSTombstoned=TRUE)))",
				 encoded_name, encoded_name);
		preference_name = name;
	}
	if (ret != LDB_SUCCESS) {
		talloc_free(tmp_ctx);
		return WERR_INTERNAL_DB_ERROR;
	}
	if (res->count == 0) {
		talloc_free(tmp_ctx);
		return WERR_DNS_ERROR_NAME_DOES_NOT_EXIST;
	}

	recs = talloc_zero(mem_ctx, struct DNS_RPC_RECORDS_ARRAY);
	W_ERROR_HAVE_NO_MEMORY_AND_FREE(recs, tmp_ctx);


	LDB_TYPESAFE_QSORT(res->msgs, res->count, name, dns_name_compare);


	tree = dns_build_tree(tmp_ctx, preference_name, res);
	W_ERROR_HAVE_NO_MEMORY_AND_FREE(tree, tmp_ctx);


	base = tree;
	while (base->level != -1) {
		base = base->children[0];
	}


	if (!(select_flag & DNS_RPC_VIEW_ONLY_CHILDREN)) {
		status = dns_fill_records_array(tmp_ctx, z, record_type,
						select_flag, NULL,
						base->data, 0,
						recs, &add_names, &add_count);
		if (!W_ERROR_IS_OK(status)) {
			talloc_free(tmp_ctx);
			return status;
		}
	}


	if (!(select_flag & DNS_RPC_VIEW_NO_CHILDREN)) {
		for (i=0; i<base->num_children; i++) {
			node = base->children[i];

			status = dns_fill_records_array(tmp_ctx, z, record_type,
							select_flag, node->name,
							node->data, node->num_children,
							recs, &add_names, &add_count);
			if (!W_ERROR_IS_OK(status)) {
				talloc_free(tmp_ctx);
				return status;
			}
		}
	}

	TALLOC_FREE(res);
	TALLOC_FREE(tree);
	TALLOC_FREE(name);


	if (select_flag & DNS_RPC_VIEW_ADDITIONAL_DATA) {
		for (i=0; i<add_count; i++) {
			struct dnsserver_zone *z2 = NULL;
			struct ldb_message *msg = NULL;

			for (z2 = dsstate->zones; z2; z2 = z2->next) {
				char *encoded_name;
				name = dns_split_node_name(tmp_ctx, add_names[i], z2->name);
				encoded_name
					= ldb_binary_encode_string(tmp_ctx,
								   name);
				ret = ldb_search(dsstate->samdb, tmp_ctx, &res, z2->zone_dn,
						LDB_SCOPE_ONELEVEL, attrs,
						"(&(objectClass=dnsNode)(name=%s)(!(dNSTombstoned=TRUE)))",
						encoded_name);
				TALLOC_FREE(name);
				if (ret != LDB_SUCCESS) {
					continue;
				}
				if (res->count == 1) {
					msg = res->msgs[0];
					break;
				} else {
					TALLOC_FREE(res);
					continue;
				}
			}

			len = strlen(add_names[i]);
			if (add_names[i][len-1] == '.') {
				rname = talloc_strdup(tmp_ctx, add_names[i]);
			} else {
				rname = talloc_asprintf(tmp_ctx, "%s.", add_names[i]);
			}
			status = dns_fill_records_array(tmp_ctx, NULL, DNS_TYPE_A,
							select_flag, rname,
							msg, 0, recs,
							NULL, NULL);
			TALLOC_FREE(rname);
			TALLOC_FREE(res);
			if (!W_ERROR_IS_OK(status)) {
				talloc_free(tmp_ctx);
				return status;
			}
		}
	}

	*buffer_length = ndr_size_DNS_RPC_RECORDS_ARRAY(recs, 0);
	*buffer = recs;

	return WERR_OK;
}
