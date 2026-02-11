do_kimage_alloc_init(void)
{
	struct kimage *image;


	image = kzalloc(sizeof(*image), GFP_KERNEL);
	if (!image)
		return NULL;

	image->head = 0;
	image->entry = &image->head;
	image->last_entry = &image->head;
	image->control_page = ~0;
	image->type = KEXEC_TYPE_DEFAULT;


	INIT_LIST_HEAD(&image->control_pages);


	INIT_LIST_HEAD(&image->dest_pages);


	INIT_LIST_HEAD(&image->unusable_pages);

	return image;
}
