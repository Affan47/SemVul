qinstance_state_append_to_dstring(const lListElem *this_elem, dstring *string)
{
   bool ret = true;
   int i = 0;

   DENTER(QINSTANCE_STATE_LAYER, "qinstance_state_append_to_dstring");
   while (states[i] != 0) {
      if (qinstance_has_state(this_elem, states[i])) {
         sge_dstring_append_char(string, letters[i]);
      }
      i++;
   }
   sge_dstring_sprintf_append(string, "%c", '\0');

   DRETURN(ret);
}
