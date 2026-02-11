objlayout_io_set_result(struct objlayout_io_res *oir, unsigned index,
			struct pnfs_osd_objid *pooid, int osd_error,
			u64 offset, u64 length, bool is_write)
{
	struct pnfs_osd_ioerr *ioerr = &oir->ioerrs[index];

	BUG_ON(index >= oir->num_comps);
	if (osd_error) {
		ioerr->oer_component = *pooid;
		ioerr->oer_comp_offset = offset;
		ioerr->oer_comp_length = length;
		ioerr->oer_iswrite = is_write;
		ioerr->oer_errno = osd_error;

		dprintk("%s: err[%d]: errno=%d is_write=%d dev(%llx:%llx) "
			"par=0x%llx obj=0x%llx offset=0x%llx length=0x%llx\n",
			__func__, index, ioerr->oer_errno,
			ioerr->oer_iswrite,
			_DEVID_LO(&ioerr->oer_component.oid_device_id),
			_DEVID_HI(&ioerr->oer_component.oid_device_id),
			ioerr->oer_component.oid_partition_id,
			ioerr->oer_component.oid_object_id,
			ioerr->oer_comp_offset,
			ioerr->oer_comp_length);
	} else {

		ioerr->oer_errno = 0;
	}
}
