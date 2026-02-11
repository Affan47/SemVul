updateStatusBar( int level, int score, int highscore )
{
    statusBar()->changeItem( i18n("Level: %1 (%2)", level, m_gameWid->levelSet().visibleName()), LEVEL_BAR_ID );
    statusBar()->changeItem( i18n("Current score: %1", score), CUR_SCORE_BAR_ID );
    QString str;
    if(highscore == 0)
        str = '-';
    else
        str.setNum(highscore);
    statusBar()->changeItem( i18n("Highscore: %1", str), HIGHSCORE_BAR_ID );
}
