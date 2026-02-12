static int run_decode_and_handler (BODY *b, STATE *s, handler_t handler, int plaintext)
{
  int origType;
  char *savePrefix = NULL;
  FILE *fp = NULL;
  BUFFER *tempfile = NULL;
  size_t tmplength = 0;
  LOFF_T tmpoffset = 0;
  int decode = 0;
  int rc = 0;

  fseeko (s->fpin, b->offset, SEEK_SET);


  if (b->encoding == ENCBASE64 || b->encoding == ENCQUOTEDPRINTABLE ||
      b->encoding == ENCUUENCODED || plaintext ||
      mutt_is_text_part (b))


  {
    origType = b->type;

    if (!plaintext)
    {

      fp = s->fpout;
      tempfile = mutt_buffer_pool_get ();
      mutt_buffer_mktemp (tempfile);
      if ((s->fpout = safe_fopen (mutt_b2s (tempfile), "w")) == NULL)
      {
        mutt_error _("Unable to open temporary file!");
        dprint (1, (debugfile, "Can't open %s.\n", mutt_b2s (tempfile)));
        mutt_buffer_pool_release (&tempfile);
        return -1;
      }


      tmplength = b->length;
      tmpoffset = b->offset;


      savePrefix = s->prefix;
      s->prefix = NULL;

      decode = 1;
    }
    else
      b->type = TYPETEXT;

    mutt_decode_attachment (b, s);

    if (decode)
    {
      b->length = ftello (s->fpout);
      b->offset = 0;
      safe_fclose (&s->fpout);


      s->fpout = fp;
      fp = s->fpin;
      s->fpin = fopen (mutt_b2s (tempfile), "r");
      unlink (mutt_b2s (tempfile));
      mutt_buffer_pool_release (&tempfile);


      s->prefix = savePrefix;
    }

    b->type = origType;
  }


  if (handler)
  {
    rc = handler (b, s);

    if (rc)
    {
      dprint (1, (debugfile, "Failed on attachment of type %s/%s.\n", TYPE(b), NONULL (b->subtype)));
    }

    if (decode)
    {
      b->length = tmplength;
      b->offset = tmpoffset;


      safe_fclose (&s->fpin);
      s->fpin = fp;
    }
  }
  s->flags |= MUTT_FIRSTDONE;

  return rc;
}
