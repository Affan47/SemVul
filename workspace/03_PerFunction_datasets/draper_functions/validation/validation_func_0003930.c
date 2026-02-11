mousePressEvent(QMouseEvent *event)
{
    if (gamePaused) {
        return;
    }

    if (event->button() == Qt::LeftButton) {
        if (TimerState == Demo) {
            stopDemoMode();
        } else if (showMatch) {
            stopMatchAnimation();
        }

        if (showHelp) {
            helpMoveStop();
        }

        if (MouseClickPos1.e == Game->m_depth) {
            transformPointToPosition(event->pos(), MouseClickPos1);

            if (MouseClickPos1.e != Game->m_depth && showMatch) {
                matchCount = Game->findAllMatchingTiles(MouseClickPos1);
                TimerState = Match;
                iTimerStep = 1;
                matchAnimationTimeout();
                cheatsUsed++;
            }
        } else {
            transformPointToPosition(event->pos(), MouseClickPos2);
            if (MouseClickPos2.e == Game->m_depth) {
                cancelUserSelectedTiles();
            } else {
                if (Game->isMatchingTile(MouseClickPos1, MouseClickPos2)) {


                    Game->setRemovedTilePair(MouseClickPos1, MouseClickPos2);


                    removeTile(MouseClickPos1, false);
                    removeTile(MouseClickPos2);


                    Game->allow_redo = false;
                    demoModeChanged(false);
                    drawTileNumber();


                    if (Game->TileNum == 0) {
                        gameOver(Game->MaxTileNum,cheatsUsed);
                    } else {

                        validMovesAvailable();
                    }
                } else {

                    hilightTile(MouseClickPos1, false, false);
                    hilightTile(MouseClickPos2, false);
                }

                MouseClickPos1.e = Game->m_depth;
                MouseClickPos2.e = Game->m_depth;
            }
        }
    }
}
