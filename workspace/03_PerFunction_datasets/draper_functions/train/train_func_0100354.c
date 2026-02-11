range_list_print_to_string(const lList *this_list,
                           dstring *string, bool ignore_step,
                           bool comma_as_separator, bool print_always_as_range)
{
   DENTER(RANGE_LAYER, "range_list_print_to_string");
   if (string != NULL) {
      if (this_list != NULL) {
         lListElem *range;

         for_each(range, this_list) {
            u_long32 start, end, step;

            range_get_all_ids(range, &start, &end, &step);
            range_to_dstring(start, end, step, string, ignore_step,
                             comma_as_separator, print_always_as_range);
         }
      } else {
         sge_dstring_append(string, "UNDEFINED");
      }
   }
   DRETURN_VOID;
}
