Q_Find(queue *q, void *data,
               int (*Comp)(const void *, const void *))
{
      void *d;
      d = Q_First(q);
      do
      {
            if (Comp(d, data) == 0)
                  return True_;
            d = Q_Next(q);
      } while (!Q_End(q));

      if (Comp(d, data) == 0)
            return True_;

      return False_;
}
