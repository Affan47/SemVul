rbd_dev_image_name(struct rbd_device *rbd_dev)
{
	size_t image_id_size;
	char *image_id;
	void *p;
	void *end;
	size_t size;
	void *reply_buf = NULL;
	size_t len = 0;
	char *image_name = NULL;
	int ret;

	rbd_assert(!rbd_dev->spec->image_name);

	len = strlen(rbd_dev->spec->image_id);
	image_id_size = sizeof (__le32) + len;
	image_id = kmalloc(image_id_size, GFP_KERNEL);
	if (!image_id)
		return NULL;

	p = image_id;
	end = image_id + image_id_size;
	ceph_encode_string(&p, end, rbd_dev->spec->image_id, (u32)len);

	size = sizeof (__le32) + RBD_IMAGE_NAME_LEN_MAX;
	reply_buf = kmalloc(size, GFP_KERNEL);
	if (!reply_buf)
		goto out;

	ret = rbd_obj_method_sync(rbd_dev, RBD_DIRECTORY,
				"rbd", "dir_get_name",
				image_id, image_id_size,
				reply_buf, size);
	if (ret < 0)
		goto out;
	p = reply_buf;
	end = reply_buf + ret;

	image_name = ceph_extract_encoded_string(&p, end, &len, GFP_KERNEL);
	if (IS_ERR(image_name))
		image_name = NULL;
	else
		dout("%s: name is %s len is %zd\n", __func__, image_name, len);
out:
	kfree(reply_buf);
	kfree(image_id);

	return image_name;
}
