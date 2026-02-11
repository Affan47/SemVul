ncredef(cdfid)
int cdfid ;
{
	NC *handle ;
	NC *new ;
	int id ;
	char *scratchfile ;

	cdf_routine_name = "ncredef" ;

	handle = NC_check_id(cdfid) ;
	if(handle == NULL)
		return(-1) ;
	if( handle->flags & NC_INDEF)
      {
          NC *stash = STASH(cdfid) ;
          if(stash) NCadvise(NC_EINDEFINE, "%s: in define mode aleady",
                             stash->path) ;
          return(-1) ;
      }
	if(!(handle->flags & NC_RDWR))
      {
          NCadvise(NC_EPERM, "%s: NC_NOWRITE", handle->path) ;
          return(-1) ;
      }


#ifdef HDF
    if(handle->file_type == HDF_FILE)
      {
          handle->flags |= NC_INDEF ;
          handle->redefid = TRUE;
          return(0);
      }
#endif


	for(id = 0 ; id < _ncdf; id++)
		if( _cdfs[id] == NULL) break ;

	if(id == _ncdf && _ncdf >= max_NC_open)
      {
          NCadvise(NC_ENFILE, "maximum number of open cdfs %d exceeded",
                   _ncdf) ;
          return(-1) ;
      }

	if( ncopts & NC_NOFILL )
      {

          handle->xdrs->x_op = XDR_ENCODE ;
          if(handle->flags & NC_NDIRTY)
            {
                if(!xdr_numrecs(handle->xdrs, handle) )
                    return(-1) ;
                handle->flags &= ~(NC_NDIRTY) ;
            }
      }

	scratchfile = NCtempname(handle->path) ;

	new = NC_dup_cdf(scratchfile, NC_NOCLOBBER, handle) ;
	if(new == NULL)
      {
          return(-1) ;
      }

	handle->flags |= NC_INDEF ;
	(void) strncpy(new->path, scratchfile, FILENAME_MAX) ;


	_cdfs[id] = handle ;
	if(id == _ncdf)
		_ncdf++ ;
	_curr_opened++;


	_cdfs[cdfid] = new ;

	new->redefid = id ;

	return(0) ;
}
