gimg_open (const char *path, int writable)
{
	struct gimg_struct *img = (struct gimg_struct *)malloc(sizeof(struct gimg_struct));

	img->path = path;
	if (map_img(path, writable, &img->base, &img->size))
		goto errout;
	if (parse_img(img))
		goto errout;
	return img;

errout:
	free(img);
	return NULL;
}
