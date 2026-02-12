static void next_lookup(struct host_query *hquery, int status)
{
  switch (*hquery->remaining_lookups)
    {
      case 'b':

          if (next_dns_lookup(hquery))
            break;
          hquery->remaining_lookups++;
          next_lookup(hquery, status);
          break;

      case 'f':

          if (file_lookup(hquery) == ARES_SUCCESS)
            {
              end_hquery(hquery, ARES_SUCCESS);
              break;
            }
          hquery->remaining_lookups++;
          next_lookup(hquery, status);
          break;
      default:

         end_hquery(hquery, status);
         break;
    }
}
