mpt_work_wrapper(struct work_struct *work)
{
	struct work_queue_wrapper *wqw =
		container_of(work, struct work_queue_wrapper, work);
	struct _MPT_SCSI_HOST *hd = wqw->hd;
	MPT_ADAPTER *ioc = hd->ioc;
	struct Scsi_Host *shost = ioc->sh;
	struct scsi_device *sdev;
	int disk = wqw->disk;
	struct _CONFIG_PAGE_IOC_3 *pg3;

	kfree(wqw);

	mpt_findImVolumes(ioc);
	pg3 = ioc->raid_data.pIocPg3;
	if (!pg3)
		return;

	shost_for_each_device(sdev,shost) {
		struct scsi_target *starget = scsi_target(sdev);
		VirtTarget *vtarget = starget->hostdata;


		if (sdev->channel != 1)
			continue;


		if(vtarget->id != disk)
			continue;

		starget_printk(KERN_INFO, vtarget->starget, MYIOC_s_FMT
		    "Integrated RAID requests DV of new device\n", ioc->name);
		mptspi_dv_device(hd, sdev);
	}
	shost_printk(KERN_INFO, shost, MYIOC_s_FMT
	    "Integrated RAID detects new device %d\n", ioc->name, disk);
	scsi_scan_target(&ioc->sh->shost_gendev, 1, disk, 0, 1);
}
