CGUISpinBox(const wchar_t* text, bool border,IGUIEnvironment* environment,
			IGUIElement* parent, s32 id, const core::rect<s32>& rectangle)
: IGUISpinBox(environment, parent, id, rectangle),
	EditBox(0), ButtonSpinUp(0), ButtonSpinDown(0), StepSize(1.f),
	RangeMin(-FLT_MAX), RangeMax(FLT_MAX), FormatString(L"%f"),
	DecimalPlaces(-1)
{
	#ifdef _DEBUG
	setDebugName("CGUISpinBox");
	#endif

	CurrentIconColor = video::SColor(255,255,255,255);
	s32 ButtonWidth = 16;
	IGUISpriteBank *sb = 0;
	if (environment && environment->getSkin())
	{
		ButtonWidth = environment->getSkin()->getSize(EGDS_SCROLLBAR_SIZE);
		sb = environment->getSkin()->getSpriteBank();
	}

	ButtonSpinDown = Environment->addButton(
		core::rect<s32>(rectangle.getWidth() - ButtonWidth, rectangle.getHeight()/2 +1,
						rectangle.getWidth(), rectangle.getHeight()), this);
	ButtonSpinDown->grab();
	ButtonSpinDown->setSubElement(true);
	ButtonSpinDown->setTabStop(false);
	ButtonSpinDown->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_CENTER, EGUIA_LOWERRIGHT);

	ButtonSpinUp = Environment->addButton(
		core::rect<s32>(rectangle.getWidth() - ButtonWidth, 0,
						rectangle.getWidth(), rectangle.getHeight()/2), this);
	ButtonSpinUp->grab();
	ButtonSpinUp->setSubElement(true);
	ButtonSpinUp->setTabStop(false);
	ButtonSpinUp->setAlignment(EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_CENTER);

	const core::rect<s32> rectEdit(0, 0, rectangle.getWidth() - ButtonWidth - 1, rectangle.getHeight());
	EditBox = Environment->addEditBox(text, rectEdit, border, this, -1);
	EditBox->grab();
	EditBox->setSubElement(true);
	EditBox->setAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT, EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);

	refreshSprites();
}
