addTab(const wchar_t* caption, s32 id)
{
	IGUISkin* skin = Environment->getSkin();
	if (!skin)
		return 0;

	core::rect<s32> r;
	if ( VerticalAlignment == EGUIA_UPPERLEFT )
	{
		r.UpperLeftCorner.X = 1;
		r.UpperLeftCorner.Y = TabHeight;

		r.LowerRightCorner.X = AbsoluteRect.getWidth()-1;
		r.LowerRightCorner.Y = AbsoluteRect.getHeight()-1;
	}
	else
	{
		r.UpperLeftCorner.X = 1;
		r.UpperLeftCorner.Y = 1;

		r.LowerRightCorner.X = AbsoluteRect.getWidth()-1;
		r.LowerRightCorner.Y = AbsoluteRect.getHeight()-TabHeight;
	}

	CGUITab* tab = new CGUITab(Tabs.size(), Environment, this, r, id);

	tab->setText(caption);
	tab->setAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	tab->setVisible(false);
	Tabs.push_back(tab);

	if (ActiveTab == -1)
	{
		ActiveTab = 0;
		tab->setVisible(true);
	}

	recalculateScrollBar();

	return tab;
}
