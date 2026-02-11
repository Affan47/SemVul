setjstatus (j)
     int j;
{
#if defined (ARRAY_VARS)
  register int i;
  register PROCESS *p;

  for (i = 1, p = jobs[j]->pipe; p->next != jobs[j]->pipe; p = p->next, i++)
    ;
  i++;
  if (statsize < i)
    {
      pstatuses = (int *)xrealloc (pstatuses, i * sizeof (int));
      statsize = i;
    }
  i = 0;
  p = jobs[j]->pipe;
  do
    {
      pstatuses[i++] = process_exit_status (p->status);
      p = p->next;
    }
  while (p != jobs[j]->pipe);

  pstatuses[i] = -1;
  set_pipestatus_array (pstatuses, i);
#endif
}
