do_transform(const char_type* p1, const char_type* p2, const U_NAMESPACE_QUALIFIER Collator* pcoll) const
{

   typedef u32_to_u16_iterator<const char_type*, ::UChar> itt;
   itt i(p1), j(p2);
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
   std::vector< ::UChar> t(i, j);
#else
   std::vector< ::UChar> t;
   while(i != j)
      t.push_back(*i++);
#endif
   ::uint8_t result[100];
   ::int32_t len;
   if(t.size())
      len = pcoll->getSortKey(&*t.begin(), static_cast< ::int32_t>(t.size()), result, sizeof(result));
   else
      len = pcoll->getSortKey(static_cast<UChar const*>(0), static_cast< ::int32_t>(0), result, sizeof(result));
   if(std::size_t(len) > sizeof(result))
   {
      scoped_array< ::uint8_t> presult(new ::uint8_t[len+1]);
      if(t.size())
         len = pcoll->getSortKey(&*t.begin(), static_cast< ::int32_t>(t.size()), presult.get(), len+1);
      else
         len = pcoll->getSortKey(static_cast<UChar const*>(0), static_cast< ::int32_t>(0), presult.get(), len+1);
      if((0 == presult[len-1]) && (len > 1))
         --len;
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
      return string_type(presult.get(), presult.get()+len);
#else
      string_type sresult;
      ::uint8_t const* ia = presult.get();
      ::uint8_t const* ib = presult.get()+len;
      while(ia != ib)
         sresult.push_back(*ia++);
      return sresult;
#endif
   }
   if((0 == result[len-1]) && (len > 1))
      --len;
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
   return string_type(result, result+len);
#else
   string_type sresult;
   ::uint8_t const* ia = result;
   ::uint8_t const* ib = result+len;
   while(ia != ib)
      sresult.push_back(*ia++);
   return sresult;
#endif
}
