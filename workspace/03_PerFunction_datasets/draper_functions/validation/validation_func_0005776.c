domain_write (GtsObject * o, FILE * fp)
{
  GfsDomain * domain = GFS_DOMAIN (o);

  if (GTS_OBJECT_CLASS (gfs_domain_class ())->parent_class->write)
    (* GTS_OBJECT_CLASS (gfs_domain_class ())->parent_class->write) (o, fp);

  fputs (" { ", fp);
  if (domain->rootlevel != 0)
    fprintf (fp, "rootlevel = %u ", domain->rootlevel);
  if (domain->refpos.x != 0.)
    fprintf (fp, "x = %g ", domain->refpos.x);
  if (domain->refpos.y != 0.)
    fprintf (fp, "y = %g ", domain->refpos.y);
  if (domain->refpos.z != 0.)
    fprintf (fp, "z = %g ", domain->refpos.z);
  if (domain->lambda.x != 1.)
    fprintf (fp, "lx = %g ", domain->lambda.x);
  if (domain->lambda.y != 1.)
    fprintf (fp, "ly = %g ", domain->lambda.y);
  if (domain->lambda.z != 1.)
    fprintf (fp, "lz = %g ", domain->lambda.z);
  fprintf (fp, "version = %d ", atoi (GFS_BUILD_VERSION));
  if (!domain->overlap)
    fputs ("overlap = 0 ", fp);
  if (domain->max_depth_write > -2) {
    GSList * i = domain->variables_io;

    if (i != NULL) {
      fprintf (fp, "variables = %s", GFS_VARIABLE1 (i->data)->name);
      i = i->next;
      while (i) {
	fprintf (fp, ",%s", GFS_VARIABLE1 (i->data)->name);
	i = i->next;
      }
      fputc (' ', fp);
    }
  }
  if (domain->binary != FALSE)
    fprintf (fp, "binary = 1 ");
  fputc ('}', fp);
}
