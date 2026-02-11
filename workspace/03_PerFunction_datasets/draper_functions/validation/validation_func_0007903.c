_raise()
{
	UT_ASSERT(m_wTopLevelWindow);
	if (GTK_IS_WINDOW (m_wTopLevelWindow))
		gtk_window_present(GTK_WINDOW (m_wTopLevelWindow));
	return true;
}
