runModal(XAP_Frame * pFrame)
{

	GtkWidget * cf = _constructWindow();
	UT_return_if_fail(cf);

	setHeightEntry();
	setWidthEntry();
	double height = UT_convertToInches(getHeightString());
	double width = UT_convertToInches(getWidthString());

	if((height > 0.0001) && (width > 0.0001))
		m_dHeightWidth = height/width;
	else
	{
		m_dHeightWidth = 0.0;
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (m_wAspectCheck), FALSE);
	}

	setWrappingGUI();
	setPositionToGUI();
	wrappingChanged();

	switch ( abiRunModalDialog ( GTK_DIALOG(cf), pFrame, this, BUTTON_CANCEL, false ) )
    {
    case GTK_RESPONSE_OK:
		event_Ok (); break;
    default:
		event_Cancel (); break;
    }

	abiDestroyWidget (cf);
}
