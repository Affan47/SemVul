inputChar(wchar_t c)
{
	if (!IsEnabled)
		return;

	if (c != 0)
	{
		if (Text.size() < Max || Max == 0)
		{
			core::stringw s;

			if (MarkBegin != MarkEnd)
			{

				const s32 realmbgn = MarkBegin < MarkEnd ? MarkBegin : MarkEnd;
				const s32 realmend = MarkBegin < MarkEnd ? MarkEnd : MarkBegin;

				s = Text.subString(0, realmbgn);
				s.append(c);
				s.append( Text.subString(realmend, Text.size()-realmend) );
				Text = s;
				CursorPos = realmbgn+1;
			}
			else
			{

				s = Text.subString(0, CursorPos);
				s.append(c);
				s.append( Text.subString(CursorPos, Text.size()-CursorPos) );
				Text = s;
				++CursorPos;
			}

			BlinkStartTime = os::Timer::getTime();
			setTextMarkers(0, 0);
		}
	}
	breakText();
	sendGuiEvent(EGET_EDITBOX_CHANGED);
	calculateScrollPos();
}
