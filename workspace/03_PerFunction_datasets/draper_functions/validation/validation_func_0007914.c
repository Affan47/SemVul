vt_mpifile_init()
{
  if( !mpifile_initialized )
  {
    struct rlimit rl;

    mpifile_gid = vt_def_file_group( VT_CURRENT_THREAD, "MPI I/O" );
    if( getrlimit(RLIMIT_NOFILE, &rl) )
      vt_error_msg( "getrlimit() failed reading max no. of open files" );
    nmaxfiles = (rl.rlim_cur == RLIM_INFINITY) ? 131072 : (int)rl.rlim_cur;
    mpifh_fid_map  = (struct mpifh_fid_map*)calloc( nmaxfiles, sizeof(struct mpifh_fid_map) );
    if( !mpifh_fid_map )
      vt_error_msg( "Out of memory while allocating %i MPI_File handles", nmaxfiles );
    nfiles = 0;

    memset( htab_mpifile, 0, sizeof(htab_mpifile) );

    mpifile_initialized = 1;
  }
}
