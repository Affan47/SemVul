institutInq(int center, int subcenter, const char *name, const char *longname)
{
  instituteInit ();

  institute_t * ip_ref = xmalloc(sizeof (*ip_ref));
  ip_ref->self       = UNDEFID;
  ip_ref->used       = 0;
  ip_ref->center     = center;
  ip_ref->subcenter  = subcenter;
  ip_ref->name       = name && name[0] ? (char *)name : NULL;
  ip_ref->longname   = longname && longname[0] ? (char *)longname : NULL;

  struct instLoc state = { .ip = ip_ref, .id = UNDEFID };
  cdiResHFilterApply(&instituteOps, findInstitute, &state);

  free(ip_ref);

  return state.id;
}
