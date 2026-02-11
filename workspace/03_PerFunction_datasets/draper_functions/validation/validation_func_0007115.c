branch( const QString& searchName )
{
   KFileTreeBranch *branch = 0;
   Q3PtrListIterator<KFileTreeBranch> it( m_branches );

   while ( (branch = it.current()) != 0 ) {
      ++it;
      QString bname = branch->name();
      kDebug(250) << "This is the branches name: " << bname;
      if( bname == searchName )
      {
	 kDebug(250) << "Found branch " << bname << " and return ptr";
	 return( branch );
      }
   }
   return ( 0L );
}
