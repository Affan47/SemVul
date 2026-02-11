static_m (GtkWidget *widget, void *data)
{
gamgi_window *window = GAMGI_CAST_WINDOW data;
GtkWidget *dialog = window->dialog0;
GtkWidget *combo;
GtkWidget *entry;
gamgi_enum style;
char token[GAMGI_ENGINE_TOKEN];
double radius;
int n, l, m;
int sampling;

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_n");
n = gtk_combo_box_get_active (GTK_COMBO_BOX (combo)) + 1;

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_l");
l = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));

combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_m");
m = gtk_combo_box_get_active (GTK_COMBO_BOX (combo)) - 5;


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_charge");
sprintf (token, "%.*f", gamgi->gamgi->charge, GAMGI_CHEM_ORBITAL_CHARGE);
gtk_entry_set_text (GTK_ENTRY (entry), token);


gamgi_chem_orbital_name (n, l, m, token);
static_name (window, token);


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_sampling");
combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_style");
style = gtk_combo_box_get_active (GTK_COMBO_BOX (combo));
if (style == STATIC_STYLE_LOCAL) gtk_entry_set_text (GTK_ENTRY (entry), "");
else
  {
  sampling = gamgi_chem_orbital_sampling (n, 1 + style);
  sprintf (token, "%d", sampling);
  gtk_entry_set_text (GTK_ENTRY (entry), token);
  }


entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_radius");
radius = gamgi_chem_orbital_radius (n, l, m, GAMGI_CHEM_ORBITAL_CHARGE);
sprintf (token, "%.*f", gamgi->gamgi->length, radius);
gtk_entry_set_text (GTK_ENTRY (entry), token);

entry = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "entry_seed");
sprintf (token, "%d", GAMGI_MATH_SEED);
gtk_entry_set_text (GTK_ENTRY (entry), token);


combo = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "combo_axes");
gtk_combo_box_set_active (GTK_COMBO_BOX (combo), FALSE);
}
