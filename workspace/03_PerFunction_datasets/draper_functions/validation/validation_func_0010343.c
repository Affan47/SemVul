close_free_lun( EnvT* e, bool freeLun)
  {
    DLong journalLUN = SysVar::JournalLUN();


    if( e->KeywordSet("ALL"))
      for( int p=maxUserLun; p<maxLun; ++p)
	{
	  if( (journalLUN-1) != p)
	    {
	      fileUnits[ p].Close();

	      fileUnits[ p].Free();
	    }
	}

    if( e->KeywordSet("FILE") || e->KeywordSet("ALL"))
      for( int p=0; p<maxUserLun; ++p)
	{
	  fileUnits[ p].Close();


	}

    int nParam=e->NParam();
    for( int p=0; p<nParam; p++)
      {
	DLong lun;
	e->AssureLongScalarPar( p, lun);
	if( lun > maxLun)
	  e->Throw( "File unit is not within allowed range: "+
		    i2s(lun)+".");
	if( lun < 1)
	  e->Throw( "File unit does not allow this operation."
		    " Unit: "+i2s(lun)+".");

	if( lun == journalLUN)
	  e->Throw(  "Reserved file cannot be closed in this manner. Unit: "+
		     i2s( lun));

	fileUnits[ lun-1].Close();
	if( freeLun) fileUnits[ lun-1].Free();
      }
  }
