__wcsmbs_named_conv (struct gconv_fcts *copy, const char *name)
{
  copy->towc = __wcsmbs_getfct ("INTERNAL", name, &copy->towc_nsteps);
  if (copy->towc == NULL)
    return 1;

  copy->tomb = __wcsmbs_getfct (name, "INTERNAL", &copy->tomb_nsteps);
  if (copy->tomb == NULL)
    {
      __gconv_close_transform (copy->towc, copy->towc_nsteps);
      return 1;
    }

  return 0;
}
