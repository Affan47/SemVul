addGroup() const
{
    QModelIndex newidx = m_model->insertGroup( m_view->currentIndex() );
    m_view->expandAll();
    m_view->setCurrentIndex( newidx );
}
