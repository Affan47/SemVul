addMoreSearchResults(struct AISLib_SearchResults * initial_results,unsigned int addedNumberOfResults)
{
  struct AISLib_SearchResults * sr = (struct AISLib_SearchResults *)  realloc(initial_results , (initial_results->resultsMAX+addedNumberOfResults)* sizeof(struct AISLib_SearchResults));
  if (sr==0)
   {
       fprintf(stderr,"Could not allocate more results ");
       return initial_results;
   }

  sr->resultsMAX += addedNumberOfResults;
  return sr;
}
