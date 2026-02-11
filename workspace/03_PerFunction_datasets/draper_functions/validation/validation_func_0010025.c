setZoomPercentage(UT_uint32 iZoom)
{
	m_iZoomPercentage = iZoom;
	XAP_App * pApp = XAP_App::getApp();
	UT_return_if_fail(pApp);
	XAP_Prefs * pPrefs = pApp->getPrefs();
	UT_return_if_fail(pPrefs);
	XAP_PrefsScheme * pScheme = pPrefs->getCurrentScheme(true);
	UT_return_if_fail(pScheme);
	UT_String sZoom;
	UT_String_sprintf(sZoom,"%d",iZoom);
	if(getZoomType() == z_PAGEWIDTH)
	{
		pScheme->setValue(XAP_PREF_KEY_ZoomType,"Width");
	}
	else if(getZoomType() == z_WHOLEPAGE)
	{
		pScheme->setValue(XAP_PREF_KEY_ZoomType,"Page");
	}
	else
	{
		pScheme->setValue(XAP_PREF_KEY_ZoomType,sZoom.c_str());
	}
	UT_DEBUGMSG(("zoom is set to %s \n",sZoom.c_str()));
	pScheme->setValue(XAP_PREF_KEY_ZoomPercentage,sZoom.c_str());
}
