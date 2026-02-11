InitHashes(FileFd &File)
{
   delete In.Hash;
   In.Hash = new Hashes;


   File.Truncate(StartPos);
   return In.Hash->AddFD(File, StartPos);
}
