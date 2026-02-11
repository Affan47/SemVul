H5FD_mpi_comm_info_dup(MPI_Comm comm, MPI_Info info, MPI_Comm *comm_new, MPI_Info *info_new)
{
    herr_t	ret_value=SUCCEED;
    MPI_Comm	comm_dup=MPI_COMM_NULL;
    MPI_Info	info_dup=MPI_INFO_NULL;
    int		mpi_code;

    FUNC_ENTER_NOAPI(FAIL)


    if (MPI_COMM_NULL == comm)
	HGOTO_ERROR(H5E_INTERNAL, H5E_BADVALUE, FAIL, "not a valid argument")
    if (!comm_new || !info_new)
	HGOTO_ERROR(H5E_INTERNAL, H5E_BADVALUE, FAIL, "bad pointers")


    if (MPI_SUCCESS != (mpi_code=MPI_Comm_dup(comm, &comm_dup)))
	HMPI_GOTO_ERROR(FAIL, "MPI_Comm_dup failed", mpi_code)
    if (MPI_INFO_NULL != info){
	if (MPI_SUCCESS != (mpi_code=MPI_Info_dup(info, &info_dup)))
	    HMPI_GOTO_ERROR(FAIL, "MPI_Info_dup failed", mpi_code)
    }else{

	info_dup = info;
    }


    *comm_new = comm_dup;
    *info_new = info_dup;

done:
    if (FAIL == ret_value){

	if (MPI_COMM_NULL != comm_dup)
	    MPI_Comm_free(&comm_dup);
	if (MPI_INFO_NULL != info_dup)
	    MPI_Info_free(&info_dup);
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
