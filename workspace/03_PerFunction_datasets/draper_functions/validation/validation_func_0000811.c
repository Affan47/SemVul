onFilterSelected()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (!action)
        return;
    if (action == d->aByCategory) {
        d->createTreeModel(Form::FormIODescription::Category);
    } else if (action == d->aByAuthor) {
        d->createTreeModel(Form::FormIODescription::Author);
    } else if (action == d->aBySpecialties) {
        d->createTreeModel(Form::FormIODescription::Specialties);
    } else if (action == d->aByType) {
        d->createTreeModel(Form::FormIODescription::TypeName);
    }
    d->ui->toolButton->setDefaultAction(action);
}
