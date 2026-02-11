blacklist(struct mei_cl_device *cldev)
{
	dev_dbg(&cldev->dev, "running hook %s on %pUl\n",
			__func__, mei_me_cl_uuid(cldev->me_cl));
	cldev->do_match = 0;
}
