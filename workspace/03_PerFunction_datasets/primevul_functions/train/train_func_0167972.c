static void usbvision_unregister_video(struct usb_usbvision *usbvision)
{

	if (video_is_registered(&usbvision->rdev)) {
		PDEBUG(DBG_PROBE, "unregister %s [v4l2]",
		       video_device_node_name(&usbvision->rdev));
		video_unregister_device(&usbvision->rdev);
	}


	if (video_is_registered(&usbvision->vdev)) {
		PDEBUG(DBG_PROBE, "unregister %s [v4l2]",
		       video_device_node_name(&usbvision->vdev));
		video_unregister_device(&usbvision->vdev);
	}
}
