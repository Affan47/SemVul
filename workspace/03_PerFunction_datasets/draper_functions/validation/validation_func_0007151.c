MPIOI_File_read(MPI_File fh,
		    MPI_Offset offset,
		    int file_ptr_type,
		    void *buf,
		    int count,
		    MPI_Datatype datatype,
		    char *myname,
		    MPI_Status *status)
{
    int error_code, bufsize, buftype_is_contig, filetype_is_contig;
    int datatype_size;
    ADIO_File adio_fh;
    ADIO_Offset off;
    void *xbuf=NULL, *e32_buf=NULL;

    MPIU_THREAD_CS_ENTER(ALLFUNC,);

    adio_fh = MPIO_File_resolve(fh);


    MPIO_CHECK_FILE_HANDLE(adio_fh, myname, error_code);
    MPIO_CHECK_COUNT(adio_fh, count, myname, error_code);
    MPIO_CHECK_DATATYPE(adio_fh, datatype, myname, error_code);

    if (file_ptr_type == ADIO_EXPLICIT_OFFSET && offset < 0)
    {
	error_code = MPIO_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE,
					  myname, __LINE__, MPI_ERR_ARG,
					  "**iobadoffset", 0);
	error_code = MPIO_Err_return_file(adio_fh, error_code);
	goto fn_exit;
    }


    MPI_Type_size(datatype, &datatype_size);


    MPIO_CHECK_COUNT_SIZE(adio_fh, count, datatype_size, myname, error_code);


    if (count*datatype_size == 0)
    {
#ifdef HAVE_STATUS_SET_BYTES
       MPIR_Status_set_bytes(status, datatype, 0);
#endif
	error_code = MPI_SUCCESS;
	goto fn_exit;
    }


    MPIO_CHECK_INTEGRAL_ETYPE(adio_fh, count, datatype_size, myname, error_code);
    MPIO_CHECK_READABLE(adio_fh, myname, error_code);
    MPIO_CHECK_NOT_SEQUENTIAL_MODE(adio_fh, myname, error_code);


    ADIOI_Datatype_iscontig(datatype, &buftype_is_contig);
    ADIOI_Datatype_iscontig(adio_fh->filetype, &filetype_is_contig);

    ADIOI_TEST_DEFERRED(adio_fh, myname, &error_code);

    xbuf = buf;
    if (adio_fh->is_external32)
    {
        MPI_Aint e32_size = 0;
        error_code = MPIU_datatype_full_size(datatype, &e32_size);
        if (error_code != MPI_SUCCESS)
            goto fn_exit;

        e32_buf = ADIOI_Malloc(e32_size*count);
	xbuf = e32_buf;
    }

    if (buftype_is_contig && filetype_is_contig)
    {

	bufsize = datatype_size * count;
	if (file_ptr_type == ADIO_EXPLICIT_OFFSET) {
	    off = adio_fh->disp + adio_fh->etype_size * offset;
	}
	else  {
	    off = adio_fh->fp_ind;
	}


        if ((adio_fh->atomicity) && ADIO_Feature(adio_fh, ADIO_LOCKS)) {
            ADIOI_WRITE_LOCK(adio_fh, off, SEEK_SET, bufsize);
	}

	ADIO_ReadContig(adio_fh, xbuf, count, datatype, file_ptr_type,
			off, status, &error_code);

        if ((adio_fh->atomicity) && ADIO_Feature(adio_fh, ADIO_LOCKS)) {
            ADIOI_UNLOCK(adio_fh, off, SEEK_SET, bufsize);
	}
    }
    else
    {
	ADIO_ReadStrided(adio_fh, xbuf, count, datatype, file_ptr_type,
			  offset, status, &error_code);

    }


    if (error_code != MPI_SUCCESS)
	error_code = MPIO_Err_return_file(adio_fh, error_code);


    if (e32_buf != NULL) {
        error_code = MPIU_read_external32_conversion_fn(buf, datatype,
                count, e32_buf);
	ADIOI_Free(e32_buf);
    }

fn_exit:
    MPIU_THREAD_CS_EXIT(ALLFUNC,);

    return error_code;
}
