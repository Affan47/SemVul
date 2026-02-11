tds_data_get_info(TDSSOCKET *tds, TDSCOLUMN *col)
{
	switch (col->column_varint_size) {
	case 8:
		col->column_size = 0x7ffffffflu;
		break;
	case 5:
	case 4:
		col->column_size = tds_get_int(tds);
		break;
	case 2:

		col->column_size = tds_get_smallint(tds);

		if (col->column_size < 0 && IS_TDS72_PLUS(tds)) {
			col->column_size = 0x3ffffffflu;
			col->column_varint_size = 8;
		}
		break;
	case 1:
		col->column_size = tds_get_byte(tds);
		break;
	case 0:
		col->column_size = tds_get_size_by_type(col->column_type);
		break;
	}


	if (is_numeric_type(col->column_type)) {
		col->column_prec = tds_get_byte(tds);
		col->column_scale = tds_get_byte(tds);

	}

	if (IS_TDS71_PLUS(tds) && is_collate_type(col->on_server.column_type)) {


		tds_get_n(tds, col->column_collation, 5);
		col->char_conv =
			tds_iconv_from_collate(tds, col->column_collation);
	}


	if (is_blob_type(col->on_server.column_type)) {

		if (IS_TDS72_PLUS(tds)) {
			unsigned char num_parts = tds_get_byte(tds);

			for (; num_parts; --num_parts) {
				col->table_namelen =
				tds_get_string(tds, tds_get_smallint(tds), col->table_name, sizeof(col->table_name) - 1);
			}
		} else {
			col->table_namelen =
				tds_get_string(tds, tds_get_smallint(tds), col->table_name, sizeof(col->table_name) - 1);
		}
	} else if (IS_TDS72_PLUS(tds) && col->on_server.column_type == SYBMSXML) {
		unsigned char has_schema = tds_get_byte(tds);
		if (has_schema) {

			tds_get_string(tds, tds_get_byte(tds), NULL, 0);
			tds_get_string(tds, tds_get_byte(tds), NULL, 0);
			tds_get_string(tds, tds_get_smallint(tds), NULL, 0);
		}
	}
	return TDS_SUCCEED;
}
