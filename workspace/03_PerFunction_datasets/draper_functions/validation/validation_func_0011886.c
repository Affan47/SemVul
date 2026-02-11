_hideMenuScroll(bool bHideMenuScroll)
{
  if(bHideMenuScroll)
  {
    UT_DEBUGMSG(("Hiding Menu \n"));
    gtk_widget_hide(m_pUnixMenu->getMenuBar());
    UT_DEBUGMSG(("Hiding scrollbar \n"));
    gtk_widget_hide(m_vScroll);
  }
  else
  {
    gtk_widget_show_all(m_pUnixMenu->getMenuBar());
    gtk_widget_show_all(m_vScroll);
  }
}
