slotDataChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight )
{

    const QModelIndex parent = topLeft.parent();
    for ( int row = topLeft.row(); row <= bottomRight.row(); ++row ) {
        scene.updateRow( scene.summaryHandlingModel()->index( row, 0, parent ) );
    }
}
