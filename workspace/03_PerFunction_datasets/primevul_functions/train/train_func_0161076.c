static void rpmsg_chrdev_remove(struct rpmsg_device *rpdev)
{
	struct rpmsg_ctrldev *ctrldev = dev_get_drvdata(&rpdev->dev);
	int ret;


	ret = device_for_each_child(&ctrldev->dev, NULL, rpmsg_eptdev_destroy);
	if (ret)
		dev_warn(&rpdev->dev, "failed to nuke endpoints: %d\n", ret);

	device_del(&ctrldev->dev);
	put_device(&ctrldev->dev);
}
