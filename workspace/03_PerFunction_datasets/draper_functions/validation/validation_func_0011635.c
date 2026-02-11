argv_iter (struct argv_iterator *ai, enum argv_iter_err *err)
{
  if (ai->fp)
    {
      ssize_t len = getdelim (&ai->tok, &ai->buf_len, '\0', ai->fp);
      if (len < 0)
        {
          *err = feof (ai->fp) ? AI_ERR_EOF : AI_ERR_READ;
          return NULL;
        }

      *err = AI_ERR_OK;
      ai->item_idx++;
      return ai->tok;
    }
  else
    {
      if (*(ai->p) == NULL)
        {
          *err = AI_ERR_EOF;
          return NULL;
        }
      else
        {
          *err = AI_ERR_OK;
          return *(ai->p++);
        }
    }
}
