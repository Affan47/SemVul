save_zindex(RAZF *rz, int fd){
	int32_t i, v32;
	int is_be;
	is_be = is_big_endian();
	if(is_be) write(fd, &rz->index->size, sizeof(int));
	else {
		v32 = byte_swap_4((uint32_t)rz->index->size);
		write(fd, &v32, sizeof(uint32_t));
	}
	v32 = rz->index->size / RZ_BIN_SIZE + 1;
	if(!is_be){
		for(i=0;i<v32;i++) rz->index->bin_offsets[i]  = byte_swap_8((uint64_t)rz->index->bin_offsets[i]);
		for(i=0;i<rz->index->size;i++) rz->index->cell_offsets[i] = byte_swap_4((uint32_t)rz->index->cell_offsets[i]);
	}
	write(fd, rz->index->bin_offsets, sizeof(int64_t) * v32);
	write(fd, rz->index->cell_offsets, sizeof(int32_t) * rz->index->size);
}
