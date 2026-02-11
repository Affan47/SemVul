push_ref_static(const char *name, int index)
{
  CHECK_STACK();

  fprintf(out, "  li r%d, _%s\n", REG_STACK(reg), name);
  reg++;

  return 0;
}
