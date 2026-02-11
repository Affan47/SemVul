remove_user_from_rm_stack ( userptr_t data, size_t size ) {
	if ( data ) {
		userptr_t rm_stack = real_to_user ( rm_ss, rm_sp );
		memcpy_user ( rm_stack, 0, data, 0, size );
	}
	rm_sp += size;
}
