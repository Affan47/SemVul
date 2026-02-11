__free_thd_list(struct thread_t *thp)
{
 register struct thread_t *thp2, *thp3;

 for (thp2 = thp; thp2 != NULL;)
  {
   thp3 = thp2->thright;
   if (thp2->thofs != NULL) __free_thd_list(thp2->thofs);
   __free_1thd(thp2);
   thp2 = thp3;
  }
}
