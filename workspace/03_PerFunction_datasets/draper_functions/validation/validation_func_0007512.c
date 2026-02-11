setStretchAvailabilityTableNicely(QTableWidget* notAllowedTimesTable)
{
	notAllowedTimesTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	int q=notAllowedTimesTable->horizontalHeader()->defaultSectionSize();
	notAllowedTimesTable->horizontalHeader()->setMinimumSectionSize(q);

	notAllowedTimesTable->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	q=-1;
	for(int i=0; i<notAllowedTimesTable->verticalHeader()->count(); i++)
		if(q<notAllowedTimesTable->verticalHeader()->sectionSizeHint(i))
			q=notAllowedTimesTable->verticalHeader()->sectionSizeHint(i);
	notAllowedTimesTable->verticalHeader()->setMinimumSectionSize(q);


	for(int i=0; i<notAllowedTimesTable->rowCount(); i++){
		for(int j=0; j<notAllowedTimesTable->columnCount(); j++){
			QFont font=notAllowedTimesTable->item(i,j)->font();
			font.setBold(true);
			notAllowedTimesTable->item(i,j)->setFont(font);
		}
	}
	notAllowedTimesTable->setCornerButtonEnabled(false);
}
