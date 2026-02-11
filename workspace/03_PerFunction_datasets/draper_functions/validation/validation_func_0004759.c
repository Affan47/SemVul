OrderUnpack(string *FileList)
{
   this->FileList = FileList;


   if (FileList != 0)
   {
      WipeFlags(After);


      for (iterator I = List; I != End; ++I)
      {
	 PkgIterator P(Cache,*I);
	 if (IsMissing(P) == true && IsNow(P) == true)
	     Flag(*I,After);
      }
   }

   Primary = &pkgOrderList::DepUnPackCrit;
   Secondary = &pkgOrderList::DepConfigure;
   RevDepends = &pkgOrderList::DepUnPackDep;
   Remove = &pkgOrderList::DepRemove;
   LoopCount = -1;


   Me = this;
   qsort(List,End - List,sizeof(*List),&OrderCompareA);

   if (Debug == true)
      clog << "** Pass A" << endl;
   if (DoRun() == false)
      return false;

   if (Debug == true)
      clog << "** Pass B" << endl;
   Secondary = 0;
   if (DoRun() == false)
      return false;

   if (Debug == true)
      clog << "** Pass C" << endl;
   LoopCount = 0;
   RevDepends = 0;
   Remove = 0;
   if (DoRun() == false)
      return false;

   if (Debug == true)
      clog << "** Pass D" << endl;
   LoopCount = 0;
   Primary = &pkgOrderList::DepUnPackPre;
   if (DoRun() == false)
      return false;

   if (Debug == true)
   {
      clog << "** Unpack ordering done" << endl;

      for (iterator I = List; I != End; ++I)
      {
	 PkgIterator P(Cache,*I);
	 if (IsNow(P) == true)
	    clog << "  " << P.FullName() << ' ' << IsMissing(P) << ',' << IsFlag(P,After) << endl;
      }
   }

   return true;
}
