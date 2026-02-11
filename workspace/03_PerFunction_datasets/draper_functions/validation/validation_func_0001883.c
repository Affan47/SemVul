showOutputContextMenu( QPoint Position )
	{
		Position = QCursor::pos();
		if ( OutputList->selectedItems().count() > 0 )
			{
				ActionOutputAdd->setEnabled( false );
				ActionOutputEdit->setEnabled( true );
				ActionOutputRemove->setEnabled( true );
			}
		else
			{
				ActionOutputAdd->setEnabled( true );
				ActionOutputEdit->setEnabled( false );
				ActionOutputRemove->setEnabled( false );
			}
		OutputContextMenu->exec( Position );
	}
