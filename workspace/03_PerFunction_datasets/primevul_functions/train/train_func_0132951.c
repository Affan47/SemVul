read_eocd(struct zip *zip, const char *p, int64_t current_offset)
{
	uint16_t disk_num;
	uint32_t cd_size, cd_offset;

	disk_num = archive_le16dec(p + 4);
	cd_size = archive_le32dec(p + 12);
	cd_offset = archive_le32dec(p + 16);


	if (disk_num != 0)
		return 0;

	if (disk_num != archive_le16dec(p + 6))
		return 0;

	if (archive_le16dec(p + 10) != archive_le16dec(p + 8))
		return 0;

	if (cd_offset + cd_size > current_offset)
		return 0;


	zip->central_directory_offset = cd_offset;
	zip->central_directory_offset_adjusted = current_offset - cd_size;


	return 32;
}
