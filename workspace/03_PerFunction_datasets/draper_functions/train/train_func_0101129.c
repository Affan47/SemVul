write_file(File* filePtr)
{
	if (!write_with_record_size(filePtr, this, &visit_region_array<FileWriterVisitor>,
										 REGION_ARRAY_RECORD_SIZE))
		return 0;

	if( !filePtr->file_write( region_info_array, sizeof(RegionInfo)*region_info_count ) )
		return 0;


	filePtr->file_put_short( region_stat_count );

	if( !filePtr->file_write( region_stat_array, sizeof(RegionStat)*region_stat_count ) )
		return 0;


	int connectBit = (region_info_count -1) * (region_info_count) /2;
	int connectByte = (connectBit +7) /8;

	if( connectByte > 0)
	{
		if( !filePtr->file_write(connect_bits, connectByte) )
			return 0;
	}

	return 1;
}
