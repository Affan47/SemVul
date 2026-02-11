sg_disk_io_stats_item_copy(const sg_disk_io_stats *s, sg_disk_io_stats *d) {

	if( SG_ERROR_NONE != sg_update_string(&d->disk_name, s->disk_name) ) {
		RETURN_FROM_PREVIOUS_ERROR( "disk", sg_get_error() );
	}

	d->read_bytes = s->read_bytes;
	d->write_bytes = s->write_bytes;
	d->systime = s->systime;

	return SG_ERROR_NONE;
}
