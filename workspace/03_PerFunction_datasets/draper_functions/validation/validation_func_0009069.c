SetLineCount(int count)
{
	if (count < m_lineCount)
	{
		std::set<int> selectedLines = m_selectedLines;
		m_selectedLines.clear();
		for (std::set<int>::const_iterator iter = selectedLines.begin(); iter != selectedLines.end(); ++iter)
			if (*iter < count)
				m_selectedLines.insert(*iter);
	}
	m_lineCount = count;
	if (m_focusedLine >= count)
		m_focusedLine = -1;

	int posx, posy;
	GetViewStart(&posx, &posy);

#ifdef __WXGTK__


	wxPoint old_view;
	GetViewStart(&old_view.x, &old_view.y);
#endif

	SetScrollbars(0, m_lineHeight, 0, m_lineCount, 0, posy);

#ifdef __WXGTK__
	wxPoint new_view;
	GetViewStart(&new_view.x, &new_view.y);
	int delta_y = m_lineHeight *(old_view.y - new_view.y);

	if (delta_y)
	{
		wxWindowList::compatibility_iterator iter = GetChildren().GetFirst();
		while (iter)
		{
			wxWindow* child = iter->GetData();
			wxPoint pos = child->GetPosition();
			pos.y -= delta_y;
			child->SetPosition(pos);

			iter = iter->GetNext();
		}
	}
#endif

	Refresh();
}
