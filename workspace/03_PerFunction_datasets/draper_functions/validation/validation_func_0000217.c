cosm_scif_close(struct cosm_device *cdev)
{


	cosm_update_mic_status(cdev);
	scif_close(cdev->epd);
	cdev->epd = NULL;
	dev_dbg(&cdev->dev, "%s %d\n", __func__, __LINE__);
}
