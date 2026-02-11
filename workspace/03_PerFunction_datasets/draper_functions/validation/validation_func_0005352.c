test_cell_view (void)
{
  gchar *buffer =
    "<interface>"
    "  <object class=\"GtkListStore\" id=\"liststore1\">"
    "    <columns>"
    "      <column type=\"gchararray\"/>"
    "    </columns>"
    "    <data>"
    "      <row>"
    "        <col id=\"0\">test</col>"
    "      </row>"
    "    </data>"
    "  </object>"
    "  <object class=\"GtkWindow\" id=\"window1\">"
    "    <child>"
    "      <object class=\"GtkCellView\" id=\"cellview1\">"
    "        <property name=\"visible\">True</property>"
    "        <property name=\"model\">liststore1</property>"
    "        <child>"
    "          <object class=\"GtkCellRendererText\" id=\"renderer1\"/>"
    "          <attributes>"
    "            <attribute name=\"text\">0</attribute>"
    "          </attributes>"
    "        </child>"
    "      </object>"
    "    </child>"
    "  </object>"
    "</interface>";
  GObject *cellview;
  GObject *model, *window;
  GtkTreePath *path;
  GList *renderers;
  GObject *renderer;
  gchar *text;

  builder = builder_new_from_string (buffer, -1, NULL);
  cellview = gtk_builder_get_object (builder, "cellview1");
  cut_assert (builder);
  cut_assert (cellview);
  cut_assert (GTK_IS_CELL_VIEW (cellview));
  g_object_get (cellview, "model", &model, NULL);
  cut_assert (model);
  cut_assert (GTK_IS_TREE_MODEL (model));
  g_object_unref (model);
  path = gtk_tree_path_new_first ();
  gtk_cell_view_set_displayed_row (GTK_CELL_VIEW (cellview), path);

  renderers = gtk_cell_view_get_cell_renderers (GTK_CELL_VIEW (cellview));
  cut_assert (renderers);
  cut_assert_equal_int (1, g_list_length (renderers));

  gtk_widget_realize (GTK_WIDGET (cellview));

  renderer = g_list_nth_data (renderers, 0);
  g_list_free (renderers);
  cut_assert (renderer);
  g_object_get (renderer, "text", &text, NULL);
  cut_assert_equal_string ("test", text);
  g_free (text);
  gtk_tree_path_free (path);

  window = gtk_builder_get_object (builder, "window1");
  gtk_widget_destroy (GTK_WIDGET (window));

  g_object_unref (builder);
  builder = NULL;
}
