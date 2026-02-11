devfreq_event_add_edev(struct device *dev,
						struct devfreq_event_desc *desc)
{
	struct devfreq_event_dev *edev;
	static atomic_t event_no = ATOMIC_INIT(0);
	int ret;

	if (!dev || !desc)
		return ERR_PTR(-EINVAL);

	if (!desc->name || !desc->ops)
		return ERR_PTR(-EINVAL);

	if (!desc->ops->set_event || !desc->ops->get_event)
		return ERR_PTR(-EINVAL);

	edev = kzalloc(sizeof(struct devfreq_event_dev), GFP_KERNEL);
	if (!edev)
		return ERR_PTR(-ENOMEM);

	mutex_init(&edev->lock);
	edev->desc = desc;
	edev->enable_count = 0;
	edev->dev.parent = dev;
	edev->dev.class = devfreq_event_class;
	edev->dev.release = devfreq_event_release_edev;

	dev_set_name(&edev->dev, "event.%d", atomic_inc_return(&event_no) - 1);
	ret = device_register(&edev->dev);
	if (ret < 0) {
		put_device(&edev->dev);
		return ERR_PTR(ret);
	}
	dev_set_drvdata(&edev->dev, edev);

	INIT_LIST_HEAD(&edev->node);

	mutex_lock(&devfreq_event_list_lock);
	list_add(&edev->node, &devfreq_event_list);
	mutex_unlock(&devfreq_event_list_lock);

	return edev;
}
