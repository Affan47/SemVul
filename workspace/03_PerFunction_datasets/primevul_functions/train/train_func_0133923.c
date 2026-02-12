proto_tree_add_bitmask_len(proto_tree *parent_tree, tvbuff_t *tvb,
		       const guint offset,  const guint len, const int hf_hdr,
		       const gint ett, int * const *fields, struct expert_field* exp,
		       const guint encoding)
{
	proto_item        *item = NULL;
	header_field_info *hf;
	guint   decodable_len;
	guint   decodable_offset;
	guint32 decodable_value;
	guint64 value;

	PROTO_REGISTRAR_GET_NTH(hf_hdr, hf);
	DISSECTOR_ASSERT_FIELD_TYPE_IS_INTEGRAL(hf);

	decodable_offset = offset;
	decodable_len = MIN(len, (guint) ftype_length(hf->type));


	if (encoding == ENC_BIG_ENDIAN) {
		decodable_offset += (len - decodable_len);
	}

	if (parent_tree) {
		decodable_value = get_uint_value(parent_tree, tvb, decodable_offset,
						 decodable_len, encoding);


		item = proto_tree_add_uint(parent_tree, hf_hdr, tvb, offset, len,
					   decodable_value);
	}

	if (decodable_len < len) {

		expert_add_info_format(NULL, item, exp,
				       "Only least-significant %d of %d bytes decoded",
				       decodable_len, len);
	}

	if (item) {
		value = get_uint64_value(parent_tree, tvb, decodable_offset, decodable_len, encoding);
		proto_item_add_bitmask_tree(item, tvb, decodable_offset, decodable_len,
		    ett, fields, BMT_NO_INT|BMT_NO_TFS, FALSE, FALSE, NULL, value);
	}

	return item;
}
