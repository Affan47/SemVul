static_ok (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
gamgi_dlist *dlist_new, *dlist_old;
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
GtkTreeModel *model;
GtkTreeIter iter;
char *name;
int scope, action;


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_scope");
scope = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_action");
action = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_method");
model = gtk_combo_box_get_model (GTK_COMBO_BOX (combo));
gtk_combo_box_get_active_iter (GTK_COMBO_BOX (combo), &iter);
gtk_tree_model_get (model, &iter, 0, &name, -1);


dlist_old = static_dlist (scope, window);


if (strcmp (name, "Pick") == 0)
  dlist_new = gamgi_gtk_select_ok_pick (dlist_old, action, window);

else if (strcmp (name, "Region") == 0)
  dlist_new = gamgi_gtk_select_ok_region (dlist_old, action, window);

else if (strcmp (name, "Name") == 0)
  dlist_new = static_ok_name (dlist_old, action, window);

else if (strcmp (name, "Layer") == 0)
  dlist_new = static_ok_parent (dlist_old,
  action, GAMGI_ENGINE_LAYER, window);
else if (strcmp (name, "Assembly") == 0)
  dlist_new = static_ok_parent (dlist_old,
  action, GAMGI_ENGINE_ASSEMBLY, window);

else if (strcmp (name, "Scale") == 0)
  dlist_new = static_ok_scale (dlist_old, action, window);

else dlist_new = NULL;
free (name);


dlist_new = gamgi_engine_dlist_invert (dlist_new);


if (dlist_old != static_before && dlist_old != gamgi->assemblys)
  gamgi_engine_dlist_remove_all (dlist_old);

gamgi_engine_dlist_remove_all (static_before);
static_before = gamgi->assemblys;

if (scope == STATIC_CURRENT)
  gamgi->assemblys = dlist_new;
else
  gamgi_gtk_select_merge (&gamgi->assemblys, dlist_new);


gamgi_global_selection_update_windows (&gamgi->assemblys, "button_assembly");

static_reset (window);
}
