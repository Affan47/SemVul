itsystem (pglobal, argc, argv, pvar, pinfo)
     pointer pglobal;
     int argc ATTRIBUTE_UNUSED;
     char **argv;
     pointer pvar;
     pointer pinfo;
{
  struct sglobal *qglobal = (struct sglobal *) pglobal;
  struct sinfo *qinfo = (struct sinfo *) pinfo;
  struct stsysloc *q;
  size_t csize;

  q = (struct stsysloc *) uuconf_malloc (qglobal->pblock,
					 sizeof (struct stsysloc));
  if (q == NULL)
    {
      qglobal->ierrno = errno;
      return (UUCONF_MALLOC_FAILED
	      | UUCONF_ERROR_ERRNO
	      | UUCONF_CMDTABRET_EXIT);
    }

  csize = strlen (argv[1]) + 1;
  q->zname = uuconf_malloc (qglobal->pblock, csize);
  if (q->zname == NULL)
    {
      qglobal->ierrno = errno;
      return (UUCONF_MALLOC_FAILED
	      | UUCONF_ERROR_ERRNO
	      | UUCONF_CMDTABRET_EXIT);
    }

  q->qnext = qinfo->qlocs;
  memcpy ((pointer) q->zname, (pointer) argv[1], csize);
  q->falias = pvar != NULL;
  q->zfile = qinfo->zname;
  q->e = qinfo->e;
  q->iloc = ftell (qinfo->e);
  q->ilineno = qglobal->ilineno;

  qinfo->qlocs = q;

  return UUCONF_CMDTABRET_CONTINUE;
}
