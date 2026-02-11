OpenLogfile(const wxString & name)
{
	applog = new wxFFileOutputStream(name);
	bool ret = applog->Ok();
	if (ret) {
		FlushApplog();
		m_LogfileName = name;
	} else {
		CloseLogfile();
	}
	return ret;
}
