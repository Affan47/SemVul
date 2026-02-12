tmp_fld_check_assert(header_field_info *hfinfo)
{
	gchar* tmp_str;


	if (!hfinfo->name || !hfinfo->name[0]) {
		if (hfinfo->abbrev)

			g_error("Field (abbrev='%s') does not have a name\n",
				hfinfo->abbrev);
		else

			g_error("Field does not have a name (nor an abbreviation)\n");
	}


	if (!hfinfo->abbrev || !hfinfo->abbrev[0])
		g_error("Field '%s' does not have an abbreviation\n", hfinfo->name);


	if (hfinfo->strings != NULL) {
		switch (hfinfo->type) {
		case FT_CHAR:
		case FT_UINT8:
		case FT_UINT16:
		case FT_UINT24:
		case FT_UINT32:
		case FT_UINT40:
		case FT_UINT48:
		case FT_UINT56:
		case FT_UINT64:
		case FT_INT8:
		case FT_INT16:
		case FT_INT24:
		case FT_INT32:
		case FT_INT40:
		case FT_INT48:
		case FT_INT56:
		case FT_INT64:
		case FT_BOOLEAN:
		case FT_PROTOCOL:
		case FT_FRAMENUM:
			break;
		case FT_FLOAT:
		case FT_DOUBLE:

			if (hfinfo->display & BASE_UNIT_STRING)
				break;


		case FT_BYTES:

			if (hfinfo->display & BASE_PROTOCOL_INFO)
				break;


		default:
			g_error("Field '%s' (%s) has a 'strings' value but is of type %s"
				" (which is not allowed to have strings)\n",
				hfinfo->name, hfinfo->abbrev, ftype_name(hfinfo->type));
		}
	}


#ifdef ENABLE_CHECK_FILTER


	if ((hfinfo->strings != NULL) &&
	    !(hfinfo->display & BASE_RANGE_STRING) &&
	    !(hfinfo->display & BASE_UNIT_STRING) &&
	    !((hfinfo->display & FIELD_DISPLAY_E_MASK) == BASE_CUSTOM) &&
	    (
		    (hfinfo->type == FT_CHAR)  ||
		    (hfinfo->type == FT_UINT8)  ||
		    (hfinfo->type == FT_UINT16) ||
		    (hfinfo->type == FT_UINT24) ||
		    (hfinfo->type == FT_UINT32) ||
		    (hfinfo->type == FT_INT8)   ||
		    (hfinfo->type == FT_INT16)  ||
		    (hfinfo->type == FT_INT24)  ||
		    (hfinfo->type == FT_INT32)  )) {

		if (hfinfo->display & BASE_EXT_STRING) {
			if (hfinfo->display & BASE_VAL64_STRING) {
				const val64_string *start_values = VAL64_STRING_EXT_VS_P((const val64_string_ext*)hfinfo->strings);
				CHECK_HF_VALUE(val64_string, G_GINT64_MODIFIER, start_values);
			} else {
				const value_string *start_values = VALUE_STRING_EXT_VS_P((const value_string_ext*)hfinfo->strings);
				CHECK_HF_VALUE(value_string, "", start_values);
			}
		} else {
			const value_string *start_values = (const value_string*)hfinfo->strings;
			CHECK_HF_VALUE(value_string, "", start_values);
		}
	}

	if (hfinfo->type == FT_BOOLEAN) {
		const true_false_string *tfs = (const true_false_string*)hfinfo->strings;
		if (tfs) {
			if (strcmp(tfs->false_string, tfs->true_string) == 0) {
				g_warning("Field '%s' (%s) has identical true and false strings (\"%s\", \"%s\")",
						   hfinfo->name, hfinfo->abbrev,
						   tfs->false_string, tfs->true_string);
			}
		}
	}

	if (hfinfo->display & BASE_RANGE_STRING) {
		const range_string *rs = (const range_string*)(hfinfo->strings);
		if (rs) {
			const range_string *this_it = rs;

			do {
				if (this_it->value_max < this_it->value_min) {
					g_warning("value_range_string error:  %s (%s) entry for \"%s\" - max(%u 0x%x) is less than min(%u 0x%x)",
							  hfinfo->name, hfinfo->abbrev,
							  this_it->strptr,
							  this_it->value_max, this_it->value_max,
							  this_it->value_min, this_it->value_min);
					++this_it;
					continue;
				}

				for (const range_string *prev_it=rs; prev_it < this_it; ++prev_it) {

					if ((prev_it->value_min <= this_it->value_min) && (prev_it->value_max >= this_it->value_max)) {
						g_warning("value_range_string error:  %s (%s) hidden by earlier entry "
								  "(prev=\"%s\":  %u 0x%x -> %u 0x%x)  (this=\"%s\":  %u 0x%x -> %u 0x%x)",
								  hfinfo->name, hfinfo->abbrev,
								  prev_it->strptr, prev_it->value_min, prev_it->value_min,
								  prev_it->value_max, prev_it->value_max,
								  this_it->strptr, this_it->value_min, this_it->value_min,
								  this_it->value_max, this_it->value_max);
					}
				}
				++this_it;
			} while (this_it->strptr);
		}
	}
#endif

	switch (hfinfo->type) {

		case FT_CHAR:


			switch (FIELD_DISPLAY(hfinfo->display)) {
				case BASE_HEX:
				case BASE_OCT:
				case BASE_CUSTOM:
					break;
				case BASE_NONE:
					if (hfinfo->strings == NULL)
						g_error("Field '%s' (%s) is an integral value (%s)"
							" but is being displayed as BASE_NONE but"
							" without a strings conversion",
							hfinfo->name, hfinfo->abbrev,
							ftype_name(hfinfo->type));
					break;
				default:
					tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Unknown: 0x%x)");
					g_error("Field '%s' (%s) is a character value (%s)"
						" but is being displayed as %s\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
					wmem_free(NULL, tmp_str);
			}
			if (hfinfo->display & BASE_UNIT_STRING) {
				g_error("Field '%s' (%s) is a character value (%s) but has a unit string\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			}
			break;
		case FT_INT8:
		case FT_INT16:
		case FT_INT24:
		case FT_INT32:
		case FT_INT40:
		case FT_INT48:
		case FT_INT56:
		case FT_INT64:


			switch (FIELD_DISPLAY(hfinfo->display)) {
				case BASE_HEX:
				case BASE_OCT:
				case BASE_DEC_HEX:
				case BASE_HEX_DEC:
					tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Bit count: %d)");
					g_error("Field '%s' (%s) is signed (%s) but is being displayed unsigned (%s)\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
					wmem_free(NULL, tmp_str);
			}

		case FT_UINT8:
		case FT_UINT16:
		case FT_UINT24:
		case FT_UINT32:
		case FT_UINT40:
		case FT_UINT48:
		case FT_UINT56:
		case FT_UINT64:
			if (IS_BASE_PORT(hfinfo->display)) {
				tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Unknown: 0x%x)");
				if (hfinfo->type != FT_UINT16) {
					g_error("Field '%s' (%s) has 'display' value %s but it can only be used with FT_UINT16, not %s\n",
						hfinfo->name, hfinfo->abbrev,
						tmp_str, ftype_name(hfinfo->type));
				}
				if (hfinfo->strings != NULL) {
					g_error("Field '%s' (%s) is an %s (%s) but has a strings value\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
				}
				if (hfinfo->bitmask != 0) {
					g_error("Field '%s' (%s) is an %s (%s) but has a bitmask\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
				}
				wmem_free(NULL, tmp_str);
				break;
			}

			if (hfinfo->display == BASE_OUI) {
				tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Unknown: 0x%x)");
				if (hfinfo->type != FT_UINT24) {
					g_error("Field '%s' (%s) has 'display' value %s but it can only be used with FT_UINT24, not %s\n",
						hfinfo->name, hfinfo->abbrev,
						tmp_str, ftype_name(hfinfo->type));
				}
				if (hfinfo->strings != NULL) {
					g_error("Field '%s' (%s) is an %s (%s) but has a strings value\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
				}
				if (hfinfo->bitmask != 0) {
					g_error("Field '%s' (%s) is an %s (%s) but has a bitmask\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
				}
				wmem_free(NULL, tmp_str);
				break;
			}


			switch (FIELD_DISPLAY(hfinfo->display)) {
				case BASE_DEC:
				case BASE_HEX:
				case BASE_OCT:
				case BASE_DEC_HEX:
				case BASE_HEX_DEC:
				case BASE_CUSTOM:
					break;
				case BASE_NONE:
					if (hfinfo->strings == NULL) {
						g_error("Field '%s' (%s) is an integral value (%s)"
							" but is being displayed as BASE_NONE but"
							" without a strings conversion",
							hfinfo->name, hfinfo->abbrev,
							ftype_name(hfinfo->type));
					}
					if (hfinfo->display & BASE_SPECIAL_VALS) {
						g_error("Field '%s' (%s) is an integral value (%s)"
							" that is being displayed as BASE_NONE but"
							" with BASE_SPECIAL_VALS",
							hfinfo->name, hfinfo->abbrev,
							ftype_name(hfinfo->type));
					}
					break;

				default:
					tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Unknown: 0x%x)");
					g_error("Field '%s' (%s) is an integral value (%s)"
						" but is being displayed as %s\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
					wmem_free(NULL, tmp_str);
			}
			break;
		case FT_BYTES:
		case FT_UINT_BYTES:


			switch (FIELD_DISPLAY(hfinfo->display)) {
				case BASE_NONE:
				case SEP_DOT:
				case SEP_DASH:
				case SEP_COLON:
				case SEP_SPACE:
					break;
				default:
					tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Bit count: %d)");
					g_error("Field '%s' (%s) is an byte array but is being displayed as %s instead of BASE_NONE, SEP_DOT, SEP_DASH, SEP_COLON, or SEP_SPACE\n",
						hfinfo->name, hfinfo->abbrev, tmp_str);
					wmem_free(NULL, tmp_str);
			}
			if (hfinfo->bitmask != 0)
				g_error("Field '%s' (%s) is an %s but has a bitmask\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));

			if ((hfinfo->strings != NULL) && (!(hfinfo->display & BASE_PROTOCOL_INFO)))
				g_error("Field '%s' (%s) is an %s but has a strings value\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			break;

		case FT_PROTOCOL:
		case FT_FRAMENUM:
			if (hfinfo->display != BASE_NONE) {
				tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Bit count: %d)");
				g_error("Field '%s' (%s) is an %s but is being displayed as %s instead of BASE_NONE\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type), tmp_str);
				wmem_free(NULL, tmp_str);
			}
			if (hfinfo->bitmask != 0)
				g_error("Field '%s' (%s) is an %s but has a bitmask\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			break;

		case FT_BOOLEAN:
			break;

		case FT_ABSOLUTE_TIME:
			if (!(hfinfo->display == ABSOLUTE_TIME_LOCAL ||
			      hfinfo->display == ABSOLUTE_TIME_UTC   ||
			      hfinfo->display == ABSOLUTE_TIME_NTP_UTC   ||
			      hfinfo->display == ABSOLUTE_TIME_DOY_UTC)) {
				tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Bit count: %d)");
				g_error("Field '%s' (%s) is a %s but is being displayed as %s instead of as a time\n",
					hfinfo->name, hfinfo->abbrev, ftype_name(hfinfo->type), tmp_str);
				wmem_free(NULL, tmp_str);
			}
			if (hfinfo->bitmask != 0)
				g_error("Field '%s' (%s) is an %s but has a bitmask\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			break;

		case FT_STRING:
		case FT_STRINGZ:
		case FT_UINT_STRING:
		case FT_STRINGZPAD:
		case FT_STRINGZTRUNC:
			switch (hfinfo->display) {
				case STR_ASCII:
				case STR_UNICODE:
					break;

				default:
					tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Unknown: 0x%x)");
					g_error("Field '%s' (%s) is an string value (%s)"
						" but is being displayed as %s\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
					wmem_free(NULL, tmp_str);
			}

			if (hfinfo->bitmask != 0)
				g_error("Field '%s' (%s) is an %s but has a bitmask\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			if (hfinfo->strings != NULL)
				g_error("Field '%s' (%s) is an %s but has a strings value\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			break;

		case FT_IPv4:
			switch (hfinfo->display) {
				case BASE_NONE:
				case BASE_NETMASK:
					break;

				default:
					tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Unknown: 0x%x)");
					g_error("Field '%s' (%s) is an IPv4 value (%s)"
						" but is being displayed as %s\n",
						hfinfo->name, hfinfo->abbrev,
						ftype_name(hfinfo->type), tmp_str);
					wmem_free(NULL, tmp_str);
					break;
			}
			break;
		case FT_FLOAT:
		case FT_DOUBLE:
			if (FIELD_DISPLAY(hfinfo->display) != BASE_NONE) {
				tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Bit count: %d)");
				g_error("Field '%s' (%s) is an %s but is being displayed as %s instead of BASE_NONE\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type),
					tmp_str);
				wmem_free(NULL, tmp_str);
			}
			if (hfinfo->bitmask != 0)
				g_error("Field '%s' (%s) is an %s but has a bitmask\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			if ((hfinfo->strings != NULL) && (!(hfinfo->display & BASE_UNIT_STRING)))
				g_error("Field '%s' (%s) is an %s but has a strings value\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			break;
		default:
			if (hfinfo->display != BASE_NONE) {
				tmp_str = val_to_str_wmem(NULL, hfinfo->display, hf_display, "(Bit count: %d)");
				g_error("Field '%s' (%s) is an %s but is being displayed as %s instead of BASE_NONE\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type),
					tmp_str);
				wmem_free(NULL, tmp_str);
			}
			if (hfinfo->bitmask != 0)
				g_error("Field '%s' (%s) is an %s but has a bitmask\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			if (hfinfo->strings != NULL)
				g_error("Field '%s' (%s) is an %s but has a strings value\n",
					hfinfo->name, hfinfo->abbrev,
					ftype_name(hfinfo->type));
			break;
	}
}
