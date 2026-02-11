buildEditors(Script *script, QWidget *parent)
	{
		ParameterDefinition::buildEditors(script, parent);

		mItemListWidget = new ItemListWidget(parent);

		addEditor(mItemListWidget);
	}
