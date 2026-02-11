merge (Keyword_List *list1, Keyword_List *list2, Keyword_Comparison less)
{
  Keyword_List *result;
  Keyword_List **resultp = &result;
  for (;;)
    {
      if (!list1)
        {
          *resultp = list2;
          break;
        }
      if (!list2)
        {
          *resultp = list1;
          break;
        }
      if (less (list2->first(), list1->first()))
        {
          *resultp = list2;
          resultp = &list2->rest();


          list2 = list1; list1 = *resultp;
        }
      else
        {
          *resultp = list1;
          resultp = &list1->rest();
          list1 = *resultp;
        }
    }
  return result;
}
