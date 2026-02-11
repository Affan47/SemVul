convertToSSA()
{
   for (ArrayList::Iterator fi = allFuncs.iterator(); !fi.end(); fi.next()) {
      Function *fn = reinterpret_cast<Function *>(fi.get());
      if (!fn->convertToSSA())
         return false;
   }
   return true;
}
