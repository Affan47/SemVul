storeItem(QLanguageItem * container)
{
	if ( mSettings.mHasStorage )
	{
		QLanguageItem * other = mStorageGraphicsView->find( container );
		if ( !other )
		{
			mStorageGraphicsView->addItem( mFactory->buildLanguageItem( container ) );
		}
		else
		{
			other->setSelected(true);
		}
		container->deleteLater();
		itemRemoved( container );
	}
}
