action_set_value (ExifData *ed, ExifLog *log, ExifParams p)
{

	ExifEntry *e = action_create_value(ed, log, p.tag, p.ifd);


	convert_arg_to_entry (p.set_value, e, exif_data_get_byte_order (ed), log);
}
