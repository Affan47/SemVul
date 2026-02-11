get_numjobs(void)
{
   lnk_link_t *curr;
   int count = 0;
   for (curr=job_list.next; curr != &job_list; curr=curr->next)
      if (LNK_DATA(curr, job_elem_t, link)->precreated == 0)
         count++;
   return count;
}
