cdiCreateTimesteps(stream_t *streamptr)
{
  int ntsteps;
  int tsID;

  if ( streamptr->ntsteps < 0 || streamptr->tstepsTableSize > 0 )
    return;

  if ( streamptr->ntsteps == 0 ) ntsteps = 1;
  else ntsteps = streamptr->ntsteps;

  streamptr->tsteps = (tsteps_t *) malloc(ntsteps*sizeof(tsteps_t));
  if ( streamptr->tsteps == NULL )
    SysError("Allocation of tsteps_t failed");

  streamptr->tstepsTableSize = ntsteps;
  streamptr->tstepsNextID    = ntsteps;

  for ( tsID = 0; tsID < ntsteps; tsID++ )
    {
      tstepsInitEntry(streamptr, tsID);
      streamptr->tsteps[tsID].taxis.used = TRUE;
    }
}
