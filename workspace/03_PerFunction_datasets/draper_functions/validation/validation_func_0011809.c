set_active(bool active)
{
  if (is_active() == active)
    return;

  if (_romdi_handling)
    set_romdi(active);

  ModuleROM1::set_active(active);
}
