lam_comm_errfatal(MPI_Comm *errcomm, int *errclass, ...)
#else
void
lam_comm_errfatal(errcomm, errclass, va_alist)

MPI_Comm		*errcomm;
int			*errclass;
va_dcl
#endif

{
	MPI_Comm	comm;
	char		*errmsg;
	int		errcode;
	int		error;
	va_list		arglist;

#if __STDC__
	va_start(arglist, errclass);
#else
	va_start(arglist);
#endif
	error = va_arg(arglist, int);
	errmsg = va_arg(arglist, char *);
	va_end(arglist);

	comm = (errcomm) ? *errcomm : MPI_COMM_NULL;

	errcode = lam_mkerr(*errclass, error);
	report_error(comm, errcode, errmsg, "comm");

	if (comm != MPI_COMM_NULL) {
		MPI_Abort(comm, errcode);
	}

	kexit(error);
}
