SortByPatternList(const char *list_c)
{
   const int max_rank=1000000;
   for(int i=0; i<fnum; i++)
      files[i]->SetRank(max_rank);
   char *list=alloca_strdup(list_c);
   int rank=0;
   for(char *p=strtok(list," "); p; p=strtok(0," "), rank++)
      for(int i=0; i<fnum; i++)
	 if(files[i]->GetRank()==max_rank && !fnmatch_dir(p,files[i]))
	    files[i]->SetRank(rank);
   Sort(BYRANK);
}
