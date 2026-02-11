check_macros(World *world, guint keyval, GdkModifierType modifiers)
{
  GSList *macroptr;
  Macro  *macro;

  if (world->disable_macros) {
    return FALSE;
  }

  macroptr = world->macros;
  while (macroptr) {
    macro = (Macro *) macroptr->data;
    if (macro->enabled &&
        macro->keyval == keyval && macro->modifiers == (modifiers & GDK_MODIFIER_MASK)) {
      parse_commands(world, macro->action, strlen(macro->action));
      return TRUE;
    }
    macroptr = macroptr->next;
  }

  return FALSE;
}
