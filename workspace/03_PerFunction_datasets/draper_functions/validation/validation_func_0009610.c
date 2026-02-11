Aborted()
{
   if (Debug == true)
      clog << "Aborted, backing out" << endl;

   pkgFLCache::NodeIterator Files = FLPkg.Files();
   map_ptrloc *Last = &FLPkg->Files;


   while (Files.end() == false)
   {

      pkgFLCache::NodeIterator Nde(FLCache,FLCache.HashNode(Files));
      for (; Nde.end() == false && Files->File != Nde->File; Nde++);
      if (Nde.end() == true)
	 return _error->Error(_("Failed to locate node in its hash bucket"));

      if (snprintf(FileName,sizeof(FileName)-20,"%s/%s",
		   Nde.DirN(),Nde.File()) <= 0)
	 return _error->Error(_("The path is too long"));


      if ((Nde->Flags & pkgFLCache::Node::Diversion) != 0)
      {
	 pkgFLCache::DiverIterator Div = Nde.Diversion();


	 if (Div->OwnerPkg != FLPkg.Offset() && Div.DivertFrom() == Nde)
	 {
	    Nde = Div.DivertTo();
	    if (snprintf(FileName,sizeof(FileName)-20,"%s/%s",
			 Nde.DirN(),Nde.File()) <= 0)
	       return _error->Error(_("The diversion path is too long"));
	 }
      }


      for (; Nde.end() == false && Files->File == Nde->File; Nde++)
      {
	 if ((Nde->Flags & pkgFLCache::Node::Replaced) ==
	     pkgFLCache::Node::Replaced)
	 {
	    if (Debug == true)
	       clog << "De-replaced " << FileName << " from " << Nde.RealPackage()->Name << endl;
	    Nde->Flags &= ~pkgFLCache::Node::Replaced;
	 }
      }


      if (Debug == true)
	 clog << "Backing out " << FileName;


      if ((Files->Flags & pkgFLCache::Node::NewFile) ==
	 pkgFLCache::Node::NewFile)
      {
	 if (Debug == true)
	    clog << " [new node]" << endl;
	 pkgFLCache::Node *Tmp = Files;
	 Files++;
	 *Last = Tmp->NextPkg;
	 Tmp->NextPkg = 0;

	 FLCache.DropNode(Tmp - FLCache.NodeP);
      }
      else
      {
	 if (Debug == true)
	    clog << endl;

	 Last = &Files->NextPkg;
	 Files++;
      }
   }

   return true;
}
