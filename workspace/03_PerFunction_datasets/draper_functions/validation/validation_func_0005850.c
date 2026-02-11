on_addFilterButton_clicked()
{
    LOG(logDEBUG) << "on_addFilterButton_clicked()";

    Filter newFilter = Filter( DEFAULT_PATTERN,
            DEFAULT_FORE_COLOUR, DEFAULT_BACK_COLOUR );
    filterSet.filterList << newFilter;


    filterListWidget->addItem( DEFAULT_PATTERN );
    filterListWidget->setCurrentRow( filterListWidget->count() - 1 );
}
