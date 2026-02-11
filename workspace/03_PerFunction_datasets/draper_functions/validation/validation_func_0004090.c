ena_com_fill_hash_function(struct ena_com_dev *ena_dev,
			       enum ena_admin_hash_functions func,
			       const u8 *key, u16 key_len, u32 init_val)
{
	struct ena_rss *rss = &ena_dev->rss;
	struct ena_admin_get_feat_resp get_resp;
	struct ena_admin_feature_rss_flow_hash_control *hash_key =
		rss->hash_key;
	int rc;


	if (unlikely(key_len & 0x3))
		return -EINVAL;

	rc = ena_com_get_feature_ex(ena_dev, &get_resp,
				    ENA_ADMIN_RSS_HASH_FUNCTION,
				    rss->hash_key_dma_addr,
				    sizeof(*rss->hash_key));
	if (unlikely(rc))
		return rc;

	if (!((1 << func) & get_resp.u.flow_hash_func.supported_func)) {
		pr_err("Flow hash function %d isn't supported\n", func);
		return -EOPNOTSUPP;
	}

	switch (func) {
	case ENA_ADMIN_TOEPLITZ:
		if (key_len > sizeof(hash_key->key)) {
			pr_err("key len (%hu) is bigger than the max supported (%zu)\n",
			       key_len, sizeof(hash_key->key));
			return -EINVAL;
		}

		memcpy(hash_key->key, key, key_len);
		rss->hash_init_val = init_val;
		hash_key->keys_num = key_len >> 2;
		break;
	case ENA_ADMIN_CRC32:
		rss->hash_init_val = init_val;
		break;
	default:
		pr_err("Invalid hash function (%d)\n", func);
		return -EINVAL;
	}

	rc = ena_com_set_hash_function(ena_dev);


	if (unlikely(rc))
		ena_com_get_hash_function(ena_dev, NULL, NULL);

	return rc;
}
