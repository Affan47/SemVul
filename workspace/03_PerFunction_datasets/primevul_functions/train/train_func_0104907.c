static struct ldb_dn *ldb_kv_index_key(struct ldb_context *ldb,
				       struct ldb_kv_private *ldb_kv,
				       const char *attr,
				       const struct ldb_val *value,
				       const struct ldb_schema_attribute **ap,
				       enum key_truncation *truncation)
{
	struct ldb_dn *ret;
	struct ldb_val v;
	const struct ldb_schema_attribute *a = NULL;
	char *attr_folded = NULL;
	const char *attr_for_dn = NULL;
	int r;
	bool should_b64_encode;

	unsigned int max_key_length = ldb_kv_max_key_length(ldb_kv);
	size_t key_len = 0;
	size_t attr_len = 0;
	const size_t indx_len = sizeof(LDB_KV_INDEX) - 1;
	unsigned frmt_len = 0;
	const size_t additional_key_length = 4;
	unsigned int num_separators = 3;
	const size_t min_data = 1;
	const size_t min_key_length = additional_key_length
		+ indx_len + num_separators + min_data;

	if (attr[0] == '@') {
		attr_for_dn = attr;
		v = *value;
		if (ap != NULL) {
			*ap = NULL;
		}
	} else {
		attr_folded = ldb_attr_casefold(ldb, attr);
		if (!attr_folded) {
			return NULL;
		}

		attr_for_dn = attr_folded;

		a = ldb_schema_attribute_by_name(ldb, attr);
		if (ap) {
			*ap = a;
		}
		r = a->syntax->canonicalise_fn(ldb, ldb, value, &v);
		if (r != LDB_SUCCESS) {
			const char *errstr = ldb_errstring(ldb);


			ldb_asprintf_errstring(ldb,
					       "Failed to create index "
					       "key for attribute '%s':%s%s%s",
					       attr, ldb_strerror(r),
					       (errstr?":":""),
					       (errstr?errstr:""));
			talloc_free(attr_folded);
			return NULL;
		}
	}
	attr_len = strlen(attr_for_dn);


	if (max_key_length - attr_len < min_key_length) {
		ldb_asprintf_errstring(
			ldb,
			__location__ ": max_key_length "
			"is too small (%u) < (%u)",
			max_key_length,
			(unsigned)(min_key_length + attr_len));
		talloc_free(attr_folded);
		return NULL;
	}


	max_key_length -= additional_key_length;


	if (ldb_kv->cache->GUID_index_attribute != NULL) {
		if (strcmp(attr, LDB_KV_IDXDN) == 0) {
			should_b64_encode = false;
		} else if (strcmp(attr, LDB_KV_IDXONE) == 0) {


			should_b64_encode = false;
		} else {
			should_b64_encode
				= ldb_should_b64_encode(ldb, &v);
		}
	} else {
		should_b64_encode = ldb_should_b64_encode(ldb, &v);
	}

	if (should_b64_encode) {
		size_t vstr_len = 0;
		char *vstr = ldb_base64_encode(ldb, (char *)v.data, v.length);
		if (!vstr) {
			talloc_free(attr_folded);
			return NULL;
		}
		vstr_len = strlen(vstr);


		key_len = num_separators + indx_len + attr_len + vstr_len;
		if (key_len > max_key_length) {
			size_t excess = key_len - max_key_length;
			frmt_len = vstr_len - excess;
			*truncation = KEY_TRUNCATED;


			ret = ldb_dn_new_fmt(ldb, ldb, "%s#%s##%.*s",
					     LDB_KV_INDEX, attr_for_dn,
					     frmt_len, vstr);
		} else {
			frmt_len = vstr_len;
			*truncation = KEY_NOT_TRUNCATED;


			ret = ldb_dn_new_fmt(ldb, ldb, "%s:%s::%.*s",
					     LDB_KV_INDEX, attr_for_dn,
					     frmt_len, vstr);
		}
		talloc_free(vstr);
	} else {

		num_separators = 2;


		key_len = num_separators + indx_len + attr_len + (int)v.length;
		if (key_len > max_key_length) {
			size_t excess = key_len - max_key_length;
			frmt_len = v.length - excess;
			*truncation = KEY_TRUNCATED;


			ret = ldb_dn_new_fmt(ldb, ldb, "%s#%s#%.*s",
					     LDB_KV_INDEX, attr_for_dn,
					     frmt_len, (char *)v.data);
		} else {
			frmt_len = v.length;
			*truncation = KEY_NOT_TRUNCATED;
			ret = ldb_dn_new_fmt(ldb, ldb, "%s:%s:%.*s",
					     LDB_KV_INDEX, attr_for_dn,
					     frmt_len, (char *)v.data);
		}
	}

	if (v.data != value->data) {
		talloc_free(v.data);
	}
	talloc_free(attr_folded);

	return ret;
}
