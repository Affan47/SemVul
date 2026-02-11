nss_MD_unix_map_connect_error(int err)
{
    PRErrorCode prError;
    switch (err) {
    case EACCES:	prError = PR_ADDRESS_NOT_SUPPORTED_ERROR; break;
#if defined(UNIXWARE) || defined(SNI) || defined(NEC)


    case EIO:		prError = PR_CONNECT_REFUSED_ERROR; break;
#endif
    case ELOOP:		prError = PR_ADDRESS_NOT_SUPPORTED_ERROR; break;
    case ENOENT:	prError = PR_ADDRESS_NOT_SUPPORTED_ERROR; break;
    case ENXIO:		prError = PR_IO_ERROR; break;
    default:		nss_MD_unix_map_default_error(err); return;
    }
    PR_SetError(prError, err);
}
