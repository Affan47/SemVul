data(int column, int role) const
{
    if ((column == 5) && (role == Qt::EditRole))
        return QVariant(_eventType->formula());
    return QTreeWidgetItem::data(column, role);
}
