mxr_base_layer_register(struct mxr_layer *layer)
{
	struct mxr_device *mdev = layer->mdev;
	int ret;

	ret = video_register_device(&layer->vfd, VFL_TYPE_GRABBER, -1);
	if (ret)
		mxr_err(mdev, "failed to register video device\n");
	else
		mxr_info(mdev, "registered layer %s as /dev/video%d\n",
			layer->vfd.name, layer->vfd.num);
	return ret;
}
