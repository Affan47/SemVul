babl_model_create_name (int             components,
                        BablComponent **component)
{
  char *p = NULL;

  while (components--)
    {
      p = babl_strcat(p, (*component)->instance.name);
      component++;
    }

  return p;
}
