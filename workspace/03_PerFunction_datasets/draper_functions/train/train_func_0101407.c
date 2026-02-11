printflat (const void *node, VISIT value, int level)
{
  if (value == leaf || value == postorder)
    {
      struct known_symbol *s = *(struct known_symbol **) node;

      cumu_ticks += s->ticks;

      printf ("%6.2f%10.2f%9.2f%9" PRIdMAX "%9.2f           %s\n",
	      total_ticks ? (100.0 * s->ticks) / total_ticks : 0.0,
	      tick_unit * cumu_ticks,
	      tick_unit * s->ticks,
	      s->calls,
	      s->calls ? (s->ticks * 1000000) * tick_unit / s->calls : 0,

	      s->name);
    }
}
