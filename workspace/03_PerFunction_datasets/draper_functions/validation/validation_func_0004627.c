OTF_WBuffer_open_zlevel( const char* filename,
	OTF_FileManager* manager, OTF_FileCompression compression ) {


	OTF_WBuffer* ret= (OTF_WBuffer*) malloc( sizeof(OTF_WBuffer) );
	if( NULL == ret ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"no memory left.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		return NULL;
	}

	OTF_WBuffer_init( ret );

	if( NULL == manager ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"manager has not been specified.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		free( ret );
		ret= NULL;

		return NULL;
	}
	ret->file= OTF_File_open_zlevel( filename, manager, OTF_FILEMODE_WRITE, compression );
	if( NULL == ret->file ) {

		OTF_Error( "ERROR in function %s, file: %s, line: %i:\n "
				"OTF_File_open() failed.\n",
				__FUNCTION__, __FILE__, __LINE__ );

		free( ret );
		ret= NULL;

		return NULL;
	}

#ifdef HAVE_ZLIB
	OTF_File_setZBufferSize( ret->file, ret->zbuffersize );
#endif

	return ret;

}
