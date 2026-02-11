Valid(uint16_t code) const {
   AType* thisType = allTypes;
   int found = 0;

   while ((thisType != NULL) && (!found)) {
      if (thisType->MBRType == code) {
         found = 1;
      }
      thisType = thisType->next;
   }
   return found;
}
