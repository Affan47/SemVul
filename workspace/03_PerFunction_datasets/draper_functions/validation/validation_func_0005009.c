Get_New_Partition( Byte_Value sector_size )
{
	Partition part_temp ;
	PartitionType part_type ;
	Sector new_start, new_end;

	switch ( optionmenu_type .get_history() )
	{
		case 0	:	part_type = GParted::TYPE_PRIMARY;  break;
		case 1	:	part_type = GParted::TYPE_LOGICAL;  break;
		case 2	:	part_type = GParted::TYPE_EXTENDED; break;

		default	:	part_type = GParted::TYPE_UNALLOCATED ;
	}


	new_start = START + (Sector(spinbutton_before .get_value_as_int()) * (MEBIBYTE / sector_size)) ;
	new_end  = new_start + (Sector(spinbutton_size .get_value_as_int()) * (MEBIBYTE / sector_size)) - 1 ;


	if ( new_start < selected_partition.sector_start )
		new_start = selected_partition.sector_start ;
	if  ( new_end > selected_partition.sector_end )
		new_end = selected_partition.sector_end ;

	part_temp .status = GParted::STAT_NEW ;
	part_temp .Set(	selected_partition .device_path,
			String::ucompose( _("New Partition #%1"), new_count ),
			new_count, part_type,
			FILESYSTEMS[ optionmenu_filesystem .get_history() ] .filesystem,
			new_start, new_end,
			sector_size,
			selected_partition .inside_extended, false ) ;


	part_temp .set_label( Utils::trim( entry .get_text() ) ) ;


	if ( (part_temp.sector_start - selected_partition.sector_start) < (MEBIBYTE / sector_size) )
		part_temp.sector_start = selected_partition.sector_start ;
	if ( (selected_partition.sector_end - part_temp.sector_end) < (MEBIBYTE / sector_size) )
		part_temp.sector_end = selected_partition.sector_end ;


	if ( part_temp .type == GParted::TYPE_EXTENDED )
	{
		Partition UNALLOCATED ;
		UNALLOCATED .Set_Unallocated( part_temp .device_path,
					      part_temp .sector_start,
					      part_temp .sector_end,
					      sector_size,
					      true ) ;
		part_temp .logicals .push_back( UNALLOCATED ) ;
	}


	switch ( optionmenu_alignment .get_history() )
	{
		case  0 :  part_temp .alignment = GParted::ALIGN_CYLINDER;  break;
		case  1 :  part_temp .alignment = GParted::ALIGN_MEBIBYTE;
		           {

		               Sector diff = ( MEBIBYTE / part_temp .sector_size ) - ( part_temp .sector_end + 1 ) % ( MEBIBYTE / part_temp .sector_size ) ;
		               if (   diff
		                   && ( part_temp .sector_start % (MEBIBYTE / part_temp .sector_size ) ) > 0
		                   && ( ( part_temp .sector_end - START +1 + diff ) < total_length )
		                  )
		                   part_temp .sector_end += diff ;
		           }
		           break;
		case  2 :  part_temp .alignment = GParted::ALIGN_STRICT;  break;

		default :  part_temp .alignment = GParted::ALIGN_MEBIBYTE ;
	}

	part_temp .free_space_before = Sector(spinbutton_before .get_value_as_int()) * (MEBIBYTE / sector_size) ;

	return part_temp;
}
