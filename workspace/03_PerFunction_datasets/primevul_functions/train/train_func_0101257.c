method_encode_code (MonoDynamicImage *assembly, ReflectionMethodBuilder *mb)
{
	char flags = 0;
	guint32 idx;
	guint32 code_size;
	gint32 max_stack, i;
	gint32 num_locals = 0;
	gint32 num_exception = 0;
	gint maybe_small;
	guint32 fat_flags;
	char fat_header [12];
	guint32 int_value;
	guint16 short_value;
	guint32 local_sig = 0;
	guint32 header_size = 12;
	MonoArray *code;

	if ((mb->attrs & (METHOD_ATTRIBUTE_PINVOKE_IMPL | METHOD_ATTRIBUTE_ABSTRACT)) ||
			(mb->iattrs & (METHOD_IMPL_ATTRIBUTE_INTERNAL_CALL | METHOD_IMPL_ATTRIBUTE_RUNTIME)))
		return 0;


	if (mb->ilgen) {
		code = mb->ilgen->code;
		code_size = mb->ilgen->code_len;
		max_stack = mb->ilgen->max_stack;
		num_locals = mb->ilgen->locals ? mono_array_length (mb->ilgen->locals) : 0;
		if (mb->ilgen->ex_handlers)
			num_exception = method_count_clauses (mb->ilgen);
	} else {
		code = mb->code;
		if (code == NULL){
			char *name = mono_string_to_utf8 (mb->name);
			char *str = g_strdup_printf ("Method %s does not have any IL associated", name);
			MonoException *exception = mono_get_exception_argument (NULL, "a method does not have any IL associated");
			g_free (str);
			g_free (name);
			mono_raise_exception (exception);
		}

		code_size = mono_array_length (code);
		max_stack = 8;
	}

	stream_data_align (&assembly->code);


	maybe_small = (max_stack <= 8) && (!num_locals) && (!num_exception);
	if (maybe_small) {
		if (code_size < 64 && !(code_size & 1)) {
			flags = (code_size << 2) | 0x2;
		} else if (code_size < 32 && (code_size & 1)) {
			flags = (code_size << 2) | 0x6;
		} else {
			goto fat_header;
		}
		idx = mono_image_add_stream_data (&assembly->code, &flags, 1);

		if (mb->ilgen && mb->ilgen->num_token_fixups)
			mono_g_hash_table_insert (assembly->token_fixups, mb->ilgen, GUINT_TO_POINTER (idx + 1));
		mono_image_add_stream_data (&assembly->code, mono_array_addr (code, char, 0), code_size);
		return assembly->text_rva + idx;
	}
fat_header:
	if (num_locals)
		local_sig = MONO_TOKEN_SIGNATURE | encode_locals (assembly, mb->ilgen);


	fat_flags =  0x03;
	if (num_exception)
		fat_flags |= METHOD_HEADER_MORE_SECTS;
	if (mb->init_locals)
		fat_flags |= METHOD_HEADER_INIT_LOCALS;
	fat_header [0] = fat_flags;
	fat_header [1] = (header_size / 4 ) << 4;
	short_value = GUINT16_TO_LE (max_stack);
	memcpy (fat_header + 2, &short_value, 2);
	int_value = GUINT32_TO_LE (code_size);
	memcpy (fat_header + 4, &int_value, 4);
	int_value = GUINT32_TO_LE (local_sig);
	memcpy (fat_header + 8, &int_value, 4);
	idx = mono_image_add_stream_data (&assembly->code, fat_header, 12);

	if (mb->ilgen && mb->ilgen->num_token_fixups)
		mono_g_hash_table_insert (assembly->token_fixups, mb->ilgen, GUINT_TO_POINTER (idx + 12));

	mono_image_add_stream_data (&assembly->code, mono_array_addr (code, char, 0), code_size);
	if (num_exception) {
		unsigned char sheader [4];
		MonoILExceptionInfo * ex_info;
		MonoILExceptionBlock * ex_block;
		int j;

		stream_data_align (&assembly->code);

		sheader [0] = METHOD_HEADER_SECTION_FAT_FORMAT | METHOD_HEADER_SECTION_EHTABLE;
		num_exception *= 6 * sizeof (guint32);
		num_exception += 4;
		sheader [1] = num_exception & 0xff;
		sheader [2] = (num_exception >> 8) & 0xff;
		sheader [3] = (num_exception >> 16) & 0xff;
		mono_image_add_stream_data (&assembly->code, (char*)sheader, 4);


		for (i = mono_array_length (mb->ilgen->ex_handlers) - 1; i >= 0; --i) {
			ex_info = (MonoILExceptionInfo *)mono_array_addr (mb->ilgen->ex_handlers, MonoILExceptionInfo, i);
			if (ex_info->handlers) {
				int finally_start = ex_info->start + ex_info->len;
				for (j = 0; j < mono_array_length (ex_info->handlers); ++j) {
					guint32 val;
					ex_block = (MonoILExceptionBlock*)mono_array_addr (ex_info->handlers, MonoILExceptionBlock, j);

					val = GUINT32_TO_LE (ex_block->type);
					mono_image_add_stream_data (&assembly->code, (char*)&val, sizeof (guint32));

					val = GUINT32_TO_LE (ex_info->start);
					mono_image_add_stream_data (&assembly->code, (char*)&val, sizeof (guint32));

					if (ex_block->type == MONO_EXCEPTION_CLAUSE_FINALLY)
						val = GUINT32_TO_LE (finally_start - ex_info->start);
					else
						val = GUINT32_TO_LE (ex_info->len);
					mono_image_add_stream_data (&assembly->code, (char*)&val, sizeof (guint32));

					val = GUINT32_TO_LE (ex_block->start);
					mono_image_add_stream_data (&assembly->code, (char*)&val, sizeof (guint32));

					val = GUINT32_TO_LE (ex_block->len);
					mono_image_add_stream_data (&assembly->code, (char*)&val, sizeof (guint32));
					finally_start = ex_block->start + ex_block->len;
					if (ex_block->extype) {
						val = mono_metadata_token_from_dor (mono_image_typedef_or_ref (assembly, mono_reflection_type_get_handle ((MonoReflectionType*)ex_block->extype)));
					} else {
						if (ex_block->type == MONO_EXCEPTION_CLAUSE_FILTER)
							val = ex_block->filter_offset;
						else
							val = 0;
					}
					val = GUINT32_TO_LE (val);
					mono_image_add_stream_data (&assembly->code, (char*)&val, sizeof (guint32));


				}
			} else {
				g_error ("No clauses for ex info block %d", i);
			}
		}
	}
	return assembly->text_rva + idx;
}
