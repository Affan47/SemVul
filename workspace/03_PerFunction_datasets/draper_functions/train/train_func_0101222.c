bru_set_selection(struct v4l2_subdev *subdev,
			     struct v4l2_subdev_pad_config *cfg,
			     struct v4l2_subdev_selection *sel)
{
	struct vsp1_bru *bru = to_bru(subdev);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *compose;

	if (sel->pad == BRU_PAD_SOURCE)
		return -EINVAL;

	if (sel->target != V4L2_SEL_TGT_COMPOSE)
		return -EINVAL;


	format = vsp1_entity_get_pad_format(&bru->entity, cfg, BRU_PAD_SOURCE,
					    sel->which);
	sel->r.left = clamp_t(unsigned int, sel->r.left, 0, format->width - 1);
	sel->r.top = clamp_t(unsigned int, sel->r.top, 0, format->height - 1);


	format = vsp1_entity_get_pad_format(&bru->entity, cfg, sel->pad,
					    sel->which);
	sel->r.width = format->width;
	sel->r.height = format->height;

	compose = bru_get_compose(bru, cfg, sel->pad, sel->which);
	*compose = sel->r;

	return 0;
}
