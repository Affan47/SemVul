Merge(pkgCacheGenerator &Gen,OpProgress *Prog) const
{
   FileFd Pkg;
   if (File != "stdin")
      Pkg.Open(File, FileFd::ReadOnly);
   else
      Pkg.OpenDescriptor(STDIN_FILENO, FileFd::ReadOnly);
   if (_error->PendingError() == true)
      return false;
   edspListParser Parser(&Pkg);
   if (_error->PendingError() == true)
      return false;

   if (Prog != NULL)
      Prog->SubProgress(0,File);
   if (Gen.SelectFile(File,std::string(),*this) == false)
      return _error->Error("Problem with SelectFile %s",File.c_str());


   pkgCache::PkgFileIterator CFile = Gen.GetCurFile();
   CFile->Size = Pkg.FileSize();
   CFile->mtime = Pkg.ModificationTime();
   map_ptrloc const storage = Gen.WriteUniqString("edsp::scenario");
   CFile->Archive = storage;

   if (Gen.MergeList(Parser) == false)
      return _error->Error("Problem with MergeList %s",File.c_str());
   return true;
}
