list_properties (GType type,
                 gint  indent)
{
  GParamSpec **self;
  GParamSpec **parent = NULL;
  guint n_self;
  guint n_parent = 0;
  gint prop_no;
  gboolean first=TRUE;

  if (!type)
    return;

  self = g_object_class_list_properties (
            G_OBJECT_CLASS (g_type_class_ref (type)),
            &n_self);
  if (g_type_parent (type))
  parent = g_object_class_list_properties (
            G_OBJECT_CLASS (g_type_class_ref (g_type_parent (type))),
            &n_parent);


  for (prop_no=0;prop_no<n_self;prop_no++)
    {
      gint parent_no;
      gboolean found=FALSE;
      for (parent_no=0;parent_no<n_parent;parent_no++)
        if (self[prop_no]==parent[parent_no])
          found=TRUE;


      if (!found)
        {

          if (first)
            {
               fprintf (file, "<h5>Properties</h5><dl>");
               first = FALSE;
            }
          fprintf (file, "<dt><b>%s</b> <em>%s</em></dt><dd>%s</dd>\n",
              g_param_spec_get_name (self[prop_no]),
              g_type_name (G_OBJECT_TYPE(self[prop_no])),
              escape(g_param_spec_get_blurb (self[prop_no])));
        }
    }
  if (!first)
    fprintf (file, "</dl>\n");

  first = TRUE;

  for (prop_no=0;prop_no<n_self;prop_no++)
    {
      gint parent_no;
      gboolean found=FALSE;
      for (parent_no=0;parent_no<n_parent;parent_no++)
        if (self[prop_no]==parent[parent_no])
          found=TRUE;


      if (found)
        {
          if (first)
            {
               fprintf (file, "<h5>Inherited Properties</h5><dl>");
               first = FALSE;
            }
          fprintf (file, "<dt><b>%s</b> <em>%s</em></dt><dd>%s</dd>\n",
              g_param_spec_get_name (self[prop_no]),
              g_type_name (G_OBJECT_TYPE(self[prop_no])),
              escape(g_param_spec_get_blurb (self[prop_no])));
        }
    }
  if (!first)
    fprintf (file, "</dl>\n");


  if (self)
    g_free (self);
  if (parent)
    g_free (parent);
}
