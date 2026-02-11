bc_write (GtsObject * o, FILE * fp)
{
  g_assert (GFS_BC (o)->v);
  fprintf (fp, "%s %s", o->klass->info.name, GFS_BC (o)->v->name);
}
