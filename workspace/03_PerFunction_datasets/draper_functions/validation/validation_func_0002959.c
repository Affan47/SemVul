updateTileDisplay()
{
    int numberOfTiles = (m_board->xTiles() * m_board->yTiles());
    QString message = i18n("Removed: %1/%2 ",
                           QString().sprintf("%d", numberOfTiles - m_board->tilesLeft()),
                           QString().sprintf("%d", numberOfTiles));

    m_gameTilesLabel->setText(message);
}
