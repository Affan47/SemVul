mono_mb_emit_i8 (MonoMethodBuilder *mb, gint64 data)
{
	if ((mb->pos + 8) >= mb->code_size) {
		mb->code_size += mb->code_size >> 1;
		mb->code = (unsigned char *)g_realloc (mb->code, mb->code_size);
	}

	mono_mb_patch_addr (mb, mb->pos, data);
	mono_mb_patch_addr (mb, mb->pos + 4, data >> 32);
	mb->pos += 8;
}
