GetIndexByName(const wxString & name) const
{
   int cnt = (int) mNodes.GetCount();


   for (int i = 0; i < cnt; i++)
   {
      if (name.CmpNoCase(mNodes[i].name) == 0)
      {
         return mNodes[i].index;
      }
   }

   return wxNOT_FOUND;
}
