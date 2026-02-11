gconf_listeners_remove  (GConfListeners* listeners,
                         guint cnxn_id)
{
  LTable* lt = (LTable*)listeners;


  if (cnxn_id == 0)
    return;

  ltable_remove(lt, cnxn_id);
}
