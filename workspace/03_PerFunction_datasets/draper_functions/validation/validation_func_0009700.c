addToolBoxAction(QAction *action)
{
    d->createToolBox();
    if (d->toolBox) {
        d->toolBox.data()->addTool(action);
    }
}
