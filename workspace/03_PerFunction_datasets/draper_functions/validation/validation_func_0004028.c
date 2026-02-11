mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    if (ColorCode::INSTANCE->GetGameState() == ColorCode::STATE_PAUSED)
    {
        return;
    }

    if (e->button() != Qt::LeftButton)
    {
        return;
    }

    if (mGameMode == ColorCode::MODE_HVM)
    {
        bool disabled = false;
        if (mActive && !mSolved)
        {
            if (e->button() == Qt::LeftButton)
            {
                SetActive(false);
                emit HintPressedSignal(mIx);
                disabled = true;
            }
        }

        if (!disabled)
        {
            QGraphicsItem::mousePressEvent(e);
        }
    }
    else if (mGameMode == ColorCode::MODE_MVH)
    {
        qreal xm = e->pos().x();
        qreal ym = e->pos().y();

        int posix = mPegCnt - 2;
        for (int i = 0; i < mPegCnt; i++)
        {
            if ( xm >= mPegPos[posix][i][0] && xm <= mPegPos[posix][i][0] + mPegPos[posix][i][2]
                 && ym >= mPegPos[posix][i][1] && ym <= mPegPos[posix][i][1] + mPegPos[posix][i][2])
            {
                ++mHints.at(i);
                if (mHints.at(i) > 2)
                {
                    mHints.at(i) = 0;
                }
            }
        }
        update(boundingRect());
    }
}
