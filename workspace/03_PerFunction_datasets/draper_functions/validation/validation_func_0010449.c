copy( const Partition & src_part,
		       Partition & dest_part,
		       OperationDetail & operationdetail )
{

	operationdetail .add_child(
	    OperationDetail(

	                     String::ucompose( _("Partition copy action skipped because %1 file system does not contain data")
	                                     , Utils::get_filesystem_string( FS_LINUX_SWAP )
	                                     )
	                   , STATUS_NONE
	                   , FONT_ITALIC
	                   )
	                          ) ;

	return true ;
}

}
