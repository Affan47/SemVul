msgdomain_list_sort_filepos (msgdomain_list_ty *mdlp)
{
  size_t j, k;

  for (k = 0; k < mdlp->nitems; k++)
    {
      message_list_ty *mlp = mdlp->item[k]->messages;

      for (j = 0; j < mlp->nitems; j++)
        {
          message_ty *mp = mlp->item[j];

          if (mp->filepos_count > 0)
            qsort (mp->filepos, mp->filepos_count, sizeof (mp->filepos[0]),
                   cmp_filepos);
        }
    }
}
