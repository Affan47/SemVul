AddOrIdent(bool const Add)
{
   pkgUdevCdromDevices UdevCdroms;
   pkgCdromTextStatus log;
   pkgCdrom cdrom;

   bool oneSuccessful = false;
   bool AutoDetect = _config->FindB("Acquire::cdrom::AutoDetect", true);
   if (AutoDetect == true && UdevCdroms.Dlopen() == true)
   {
      bool const Debug = _config->FindB("Debug::Acquire::cdrom", false);
      std::string const CDMount = _config->Find("Acquire::cdrom::mount");
      bool const NoMount = _config->FindB("APT::CDROM::NoMount", false);
      if (NoMount == false)
	 _config->Set("APT::CDROM::NoMount", true);

      vector<struct CdromDevice> const v = UdevCdroms.Scan();
      for (std::vector<struct CdromDevice>::const_iterator cd = v.begin(); cd != v.end(); ++cd)
      {
	 if (Debug)
	    clog << "Looking at device:"
	       << "\tDeviveName: '" << cd->DeviceName << "'"
	       << "\tIsMounted: '" << cd->Mounted << "'"
	       << "\tMountPoint: '" << cd->MountPath << "'"
	       << endl;

	 std::string AptMountPoint;
	 if (cd->Mounted)
	    _config->Set("Acquire::cdrom::mount", cd->MountPath);
	 else if (NoMount == true)
	    continue;
	 else
	 {
	    AptMountPoint = _config->FindDir("Dir::Media::MountPath");
	    if (FileExists(AptMountPoint) == false)
	       mkdir(AptMountPoint.c_str(), 0750);
	    if(MountCdrom(AptMountPoint, cd->DeviceName) == false)
	    {
	       _error->Warning(_("Failed to mount '%s' to '%s'"), cd->DeviceName.c_str(), AptMountPoint.c_str());
	       continue;
	    }
	    _config->Set("Acquire::cdrom::mount", AptMountPoint);
	 }

	 _error->PushToStack();
	 if (Add == true)
	    oneSuccessful = cdrom.Add(&log);
	 else
	 {
	    std::string id;
	    oneSuccessful = cdrom.Ident(id, &log);
	 }
	 _error->MergeWithStack();

	 if (AptMountPoint.empty() == false)
	    UnmountCdrom(AptMountPoint);
      }
      if (NoMount == false)
	 _config->Set("APT::CDROM::NoMount", NoMount);
      _config->Set("Acquire::cdrom::mount", CDMount);
   }


   if (oneSuccessful == false)
   {
      _error->PushToStack();
      if (Add == true)
	 oneSuccessful = cdrom.Add(&log);
      else
      {
	 std::string id;
	 oneSuccessful = cdrom.Ident(id, &log);
      }
      _error->MergeWithStack();
   }

   if (oneSuccessful == false)
      _error->Error("%s", _("No CD-ROM could be auto-detected or found using the default mount point.\n"
      "You may try the --cdrom option to set the CD-ROM mount point.\n"
      "See 'man apt-cdrom' for more information about the CD-ROM auto-detection and mount point."));
   else if (Add == true)
      cout << _("Repeat this process for the rest of the CDs in your set.") << endl;

   return oneSuccessful;
}
