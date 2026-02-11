_k_search()
{
    if (searchLine->text().isEmpty()) {
        return;
    }
    searchMode = true;
    const QList<QChar> contents = s_data->find(searchLine->text());
    charTable->setContents(contents);
    emit q->displayedCharsChanged();
    if (!contents.isEmpty()) {
        charTable->setChar(contents[0]);
    }
}
