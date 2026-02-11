_gcry_mpi_resize (gcry_mpi_t a, unsigned nlimbs)
{
  size_t i;

  if (nlimbs <= a->alloced)
    {


      for (i=a->nlimbs; i < a->alloced; i++)
        a->d[i] = 0;
      return;
    }


  if (a->d)
    {
      a->d = xrealloc (a->d, nlimbs * sizeof (mpi_limb_t));
      for (i=a->alloced; i < nlimbs; i++)
        a->d[i] = 0;
    }
  else
    {
      if (a->flags & 1)

	a->d = xcalloc_secure (nlimbs , sizeof (mpi_limb_t));
      else

	a->d = xcalloc (nlimbs , sizeof (mpi_limb_t));
    }
  a->alloced = nlimbs;
}
