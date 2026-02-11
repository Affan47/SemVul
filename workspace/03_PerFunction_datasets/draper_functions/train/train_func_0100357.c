efi_file_read ( EFI_FILE_PROTOCOL *this,
					 UINTN *len, VOID *data ) {
	struct efi_file *file = container_of ( this, struct efi_file, file );
	size_t remaining;


	if ( ! file->image )
		return efi_file_read_dir ( file, len, data );


	remaining = ( file->image->len - file->pos );
	if ( *len > remaining )
		*len = remaining;
	DBGC ( file, "EFIFILE %s read [%#08zx,%#08zx)\n",
	       efi_file_name ( file ), file->pos,
	       ( ( size_t ) ( file->pos + *len ) ) );
	copy_from_user ( data, file->image->data, file->pos, *len );
	file->pos += *len;
	return 0;
}
