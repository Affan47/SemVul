replace(const ValueRef &repVal, bool doSet)
{
   assert(mayReplace(repVal));

   if (value == repVal.get())
      return;

   while (!value->uses.empty()) {
      ValueRef *ref = value->uses.front();
      ref->set(repVal.get());
      ref->mod *= repVal.mod;
   }

   if (doSet)
      set(repVal.get());
}
