print_caps (const char **caps) {
  while (*caps) {
    g_print ("%s", *caps++);
    if (*caps)
      g_print (", ");
  }
  g_print ("\n");
}
