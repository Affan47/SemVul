bpf_jit_binary_alloc(unsigned int proglen, u8 **image_ptr,
		     unsigned int alignment,
		     bpf_jit_fill_hole_t bpf_fill_ill_insns)
{
	struct bpf_binary_header *hdr;
	unsigned int size, hole, start;


	size = round_up(proglen + sizeof(*hdr) + 128, PAGE_SIZE);
	hdr = module_alloc(size);
	if (hdr == NULL)
		return NULL;


	bpf_fill_ill_insns(hdr, size);

	hdr->pages = size / PAGE_SIZE;
	hole = min_t(unsigned int, size - (proglen + sizeof(*hdr)),
		     PAGE_SIZE - sizeof(*hdr));
	start = (get_random_int() % hole) & ~(alignment - 1);


	*image_ptr = &hdr->image[start];

	return hdr;
}
