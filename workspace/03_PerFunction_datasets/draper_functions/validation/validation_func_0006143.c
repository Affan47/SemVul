numberOfAlarms(const QModelIndex &index) const
{
    if(index.parent().isValid())
        return 0;

    int nrofAlarms = 0;
    for(int i=0; i<index.model()->rowCount(index); i++)
        if(static_cast<Event*>(index.child(i,0).internalPointer())->hasAlarm())
            nrofAlarms++;

    return nrofAlarms;
}
