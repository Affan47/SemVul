djvu_cgi_names(void) const
{
   if(!validurl) const_cast<GURL *>(this)->init();
   GCriticalSectionLock lock((GCriticalSection *) &class_lock);

   int i;
   DArray<GUTF8String> arr;
   for(i=0;(i<cgi_name_arr.size())&&
     (cgi_name_arr[i].upcase()!=djvuopts)
     ;i++)
     	EMPTY_LOOP;

   int size=cgi_name_arr.size()-(i+1);
   if (size>0)
   {
      arr.resize(size-1);
      for(i=0;i<arr.size();i++)
         arr[i]=cgi_name_arr[cgi_name_arr.size()-arr.size()+i];
   }

   return arr;
}
