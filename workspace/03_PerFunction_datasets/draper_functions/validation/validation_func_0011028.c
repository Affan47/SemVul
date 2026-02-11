save_image(const F_CHAR *filename)
{
	FILE* file;
	F_HEADER h;

	file = OPEN_WRITE(filename);
	if(file == NULL)
	{
		print_string("Cannot open image file: "); print_native_string(filename); nl();
		print_string(strerror(errno)); nl();
		return false;
	}

	F_ZONE *tenured = &data_heap->generations[TENURED];

	h.magic = IMAGE_MAGIC;
	h.version = IMAGE_VERSION;
	h.data_relocation_base = tenured->start;
	h.data_size = tenured->here - tenured->start;
	h.code_relocation_base = code_heap.segment->start;
	h.code_size = heap_size(&code_heap);

	h.t = T;
	h.bignum_zero = bignum_zero;
	h.bignum_pos_one = bignum_pos_one;
	h.bignum_neg_one = bignum_neg_one;

	CELL i;
	for(i = 0; i < USER_ENV; i++)
	{
		if(i < FIRST_SAVE_ENV)
			h.userenv[i] = F;
		else
			h.userenv[i] = userenv[i];
	}

	bool ok = true;

	if(fwrite(&h,sizeof(F_HEADER),1,file) != 1) ok = false;
	if(fwrite((void*)tenured->start,h.data_size,1,file) != 1) ok = false;
	if(fwrite(first_block(&code_heap),h.code_size,1,file) != 1) ok = false;
	if(fclose(file)) ok = false;

	if(!ok)
	{
		print_string("save-image failed: "); print_string(strerror(errno)); nl();
	}

	return ok;
}
