get_hfi_length(header_field_info *hfinfo, tvbuff_t *tvb, const gint start, gint *length,
		   gint *item_length, const guint encoding)
{
	gint length_remaining;


	DISSECTOR_ASSERT(tvb != NULL || *length == 0);


	if (*length == -1) {


		if ((IS_FT_INT(hfinfo->type)) || (IS_FT_UINT(hfinfo->type))) {
			if (encoding & (ENC_VARINT_PROTOBUF|ENC_VARINT_ZIGZAG)) {


				*item_length = *length;
				return;
			} else if (encoding & ENC_VARINT_QUIC) {
				switch (tvb_get_guint8(tvb, start) >> 6)
				{
				case 0:
					*item_length = 1;
					break;
				case 1:
					*item_length = 2;
					break;
				case 2:
					*item_length = 4;
					break;
				case 3:
					*item_length = 8;
					break;
				}
			}
		}

		switch (hfinfo->type) {

		case FT_PROTOCOL:
		case FT_NONE:
		case FT_BYTES:
		case FT_STRING:
		case FT_STRINGZPAD:
		case FT_STRINGZTRUNC:


			*length = tvb_captured_length(tvb) ? tvb_ensure_captured_length_remaining(tvb, start) : 0;
			DISSECTOR_ASSERT(*length >= 0);
			break;

		case FT_STRINGZ:


			break;

		default:
			THROW(ReportedBoundsError);
			DISSECTOR_ASSERT_NOT_REACHED();
		}
		*item_length = *length;
	} else {
		*item_length = *length;
		if (hfinfo->type == FT_PROTOCOL || hfinfo->type == FT_NONE) {


			if (tvb) {
				length_remaining = tvb_captured_length_remaining(tvb, start);
				if (*item_length < 0 ||
					(*item_length > 0 &&
					  (length_remaining < *item_length)))
					*item_length = length_remaining;
			}
		}
		if (*item_length < 0) {
			THROW(ReportedBoundsError);
		}
	}
}
