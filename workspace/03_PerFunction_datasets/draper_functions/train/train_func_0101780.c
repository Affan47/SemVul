openOriginalToCurrentMappingFiles()
{
  dmtcp::ostringstream pidMapFile, pidMapCountFile;
  dmtcp::ostringstream shmidListFile, shmidMapFile;
  int fd;

  shmidMapFile << dmtcpTmpDir << "/dmtcpShmidMap."
     << compGroup << "." << std::hex << coordTstamp;
  shmidListFile << dmtcpTmpDir << "/dmtcpShmidList."
     << compGroup << "." << std::hex << coordTstamp;

  pidMapFile << dmtcpTmpDir << "/dmtcpPidMap."
     << compGroup << "." << std::hex << coordTstamp;
  pidMapCountFile << dmtcpTmpDir << "/dmtcpPidMapCount."
     << compGroup << "." << std::hex << coordTstamp;


  JTRACE("Open dmtcpShmidListFile")(shmidListFile.str());
  fd = openSharedFile(shmidListFile.str(), (O_WRONLY|O_APPEND));
  JASSERT ( fd != -1 );
  JASSERT ( dup2 ( fd, PROTECTED_SHMIDLIST_FD ) == PROTECTED_SHMIDLIST_FD )
	  ( shmidListFile.str() );
  close (fd);


  JTRACE("Open dmtcpShmidMapFile")(shmidMapFile.str());
  fd = openSharedFile(shmidMapFile.str(), (O_WRONLY|O_APPEND));
  JASSERT ( fd != -1 );
  JASSERT ( dup2 ( fd, PROTECTED_SHMIDMAP_FD ) == PROTECTED_SHMIDMAP_FD )
	  ( shmidMapFile.str() );
  close (fd);


  JTRACE("Open dmtcpPidMapFile")(pidMapFile.str());
  fd = openSharedFile(pidMapFile.str(), (O_WRONLY|O_APPEND));
  JASSERT ( fd != -1 );
  JASSERT ( dup2 ( fd, PROTECTED_PIDMAP_FD ) == PROTECTED_PIDMAP_FD )
	  ( pidMapFile.str() );
  close (fd);


  JTRACE("Open dmtcpPidMapCount files for writing")(pidMapCountFile.str());
  fd = openSharedFile(pidMapCountFile.str(), O_RDWR);
  JASSERT ( fd != -1 );
  JASSERT ( dup2 ( fd, PROTECTED_PIDMAPCNT_FD ) == PROTECTED_PIDMAPCNT_FD )
	  ( pidMapCountFile.str() );
  close(fd);

  Util::lockFile(PROTECTED_PIDMAPCNT_FD);


  static jalib::JBinarySerializeWriterRaw countwr(pidMapCountFile.str(),
						  PROTECTED_PIDMAPCNT_FD);
  if( countwr.isempty() ){
    JTRACE("pidMapCountFile is empty.  Initialize it with count = 0")
      (pidMapCountFile.str());
    size_t numMaps = 0;
    dmtcp::VirtualPidTable::serializeEntryCount (countwr, numMaps);
    fsync(PROTECTED_PIDMAPCNT_FD);
  }else{
    JTRACE("pidMapCountFile is not empty - do nothing");
  }

  Util::unlockFile(PROTECTED_PIDMAPCNT_FD);
}
