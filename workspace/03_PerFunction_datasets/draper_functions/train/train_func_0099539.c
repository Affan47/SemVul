ReadBBFile(const char * file,long & nbsol,long & lsol,int *& typesols,
  const int dim,const int typesol)
{

  MeshIstream frbb(file);
  int dimlu,typesollu;
  typesols = 0;
  long i,n=0;
  double *sol =0;
  int sizeoftype[] = { 1, dim ,dim * (dim+1) / 2, dim * dim } ;

  frbb >>    dimlu >> nbsol ;
  typesols = new int [nbsol] ;
  for (i=0;i<nbsol;i++)
    {
     frbb >> typesols[i];
     typesols[i]--;
     if (typesols[i]<0 || typesols[i]>= 4)
       {
	 cerr << " Error reading BBFile the type solution " << i+1 << " is " << typesols[i]+1
	      << " is not in [1..4] " << endl;
	   frbb.ShowIoErr(998);
	 nbsol=0;
	 lsol=0;
	 delete [] typesols;
	 typesols=0;
	 return 0;
       }
     n += sizeoftype[ typesols[i]];
    }
  frbb >> lsol >> typesollu ;
  if(typesol != typesollu )
    {
      cerr << " incorrect type of solution (read) " << typesollu << " != (wanted) " <<  typesol << endl;
      cerr << "  or       dim  of solution (read) " << dimlu  << " != (wanted) " <<  dim << endl;
      frbb.ShowIoErr(999);
      nbsol=0;
      lsol=0;
    }
  else
    {
      if (verbosity> 5)
	cout << "     read BB file " << file << "  with nbsol " << nbsol << " total nb of field = " << n << endl;
      if (verbosity>9)
	for (i=0;i<nbsol;i++)
	  cout << "      the type of solution " << i+1 << " is " <<  sizeoftype[ typesols[i]]
	       << " and  the number of sub-field are " << sizeoftype[ typesols[i]] << endl;
      sol = new double[lsol*n];
      double *s=sol;
      for(  i=0;i<lsol;i++)
	for (long j=0;j<n;j++)
	  frbb >>  *s++ ;

    }


  return sol;
}
