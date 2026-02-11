BuildSourceList(OpProgress * )
{
   if (SrcList != NULL)
      return true;

   SrcList = new pkgSourceList();
   if (SrcList->ReadMainList() == false)
      return _error->Error(_("The list of sources could not be read."));
   return true;
}
