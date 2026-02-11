__rep_control_marshal(env, argp, bp, max, lenp)
	ENV *env;
	__rep_control_args *argp;
	u_int8_t *bp;
	size_t *lenp, max;
{
	u_int8_t *start;

	if (max < __REP_CONTROL_SIZE)
		return (ENOMEM);
	start = bp;

	DB_HTONL_COPYOUT(env, bp, argp->rep_version);
	DB_HTONL_COPYOUT(env, bp, argp->log_version);
	DB_HTONL_COPYOUT(env, bp, argp->lsn.file);
	DB_HTONL_COPYOUT(env, bp, argp->lsn.offset);
	DB_HTONL_COPYOUT(env, bp, argp->rectype);
	DB_HTONL_COPYOUT(env, bp, argp->gen);
	DB_HTONL_COPYOUT(env, bp, argp->msg_sec);
	DB_HTONL_COPYOUT(env, bp, argp->msg_nsec);
	DB_HTONL_COPYOUT(env, bp, argp->flags);

	*lenp = (size_t)(bp - start);
	return (0);
}
