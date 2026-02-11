push(int, Packet *p)
{
  if (p->length() > _max)
    checked_output_push(1, p);
  else
    output(0).push(p);
}
