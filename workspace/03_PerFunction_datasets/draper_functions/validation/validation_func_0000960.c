toggle_istool (Client * c)
{
  if (c)
    c->istool = !c->istool;

  update_tbar ();
}
