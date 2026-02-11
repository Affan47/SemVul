csr1212_parse_keyval(struct csr1212_keyval *kv,
			 struct csr1212_csr_rom_cache *cache)
{
	struct csr1212_keyval_img *kvi;
	int i;
	int ret = CSR1212_SUCCESS;
	int kvi_len;

	kvi = (struct csr1212_keyval_img*)&cache->data[bytes_to_quads(kv->offset -
								      cache->offset)];
	kvi_len = CSR1212_BE16_TO_CPU(kvi->length);

#if 0


	if ((csr1212_crc16(kvi->data, kvi_len) != kvi->crc) &&
	    (csr1212_msft_crc16(kvi->data, kvi_len) != kvi->crc)) {
		ret = CSR1212_EINVAL;
		goto fail;
	}
#endif

	switch(kv->key.type) {
	case CSR1212_KV_TYPE_DIRECTORY:
		for (i = 0; i < kvi_len; i++) {
			csr1212_quad_t ki = kvi->data[i];


			if (ki == 0x0)
				continue;
			ret = csr1212_parse_dir_entry(kv, ki,
						      (kv->offset +
						       quads_to_bytes(i + 1)));
		}
		kv->value.directory.len = kvi_len;
		break;

	case CSR1212_KV_TYPE_LEAF:
		if (kv->key.id != CSR1212_KV_ID_EXTENDED_ROM) {
			kv->value.leaf.data = CSR1212_MALLOC(quads_to_bytes(kvi_len));
			if (!kv->value.leaf.data)
			{
				ret = CSR1212_ENOMEM;
				goto fail;
			}

			kv->value.leaf.len = kvi_len;
			memcpy(kv->value.leaf.data, kvi->data, quads_to_bytes(kvi_len));
		}
		break;
	}

	kv->valid = 1;

fail:
	return ret;
}
