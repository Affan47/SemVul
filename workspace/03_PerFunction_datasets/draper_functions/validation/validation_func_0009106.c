SetSettings()
{
    bool sup = SetSuppressSlots(true);

    mMenuBarCb->setChecked(mSettings->mShowMenuBar);
    mStatusBarCb->setChecked(mSettings->mShowStatusBar);
    mToolBarCb->setChecked(mSettings->mShowToolBar);
    mShowGameNoCb->setChecked(mSettings->mShowGameNo);

    mShowTimerCb->setChecked(mSettings->mShowTimer);
    mShowTenthCb->setChecked(mSettings->mShowTenth);
    ShowTimerChangedSlot(mShowTimerCb->checkState());

    mShowIndicatorsCb->setChecked(mSettings->mShowIndicators);
    if (mSettings->mIndicatorType == Settings::INDICATOR_NUMBER)
    {
        mNumbersRb->setChecked(true);
    }
    else
    {
        mLettersRb->setChecked(true);
    }
    mHideColorsCb->setChecked(mSettings->mHideColors);

    int i;
    i = mColorCntCmb->findData(mSettings->mColorCnt);
    if (i != -1 && mColorCntCmb->currentIndex() != i)
    {
        mColorCntCmb->setCurrentIndex(i);
    }
    i = mPegCntCmb->findData(mSettings->mPegCnt);
    if (i != -1 && mPegCntCmb->currentIndex() != i)
    {
        mPegCntCmb->setCurrentIndex(i);
    }

    mDoublesCb->setChecked(mSettings->mDoubles);
    CheckDoubles();
    CheckLevelPresets();

    i = mGameModeCmb->findData(mSettings->mGameMode);
    if (i != -1 && mGameModeCmb->currentIndex() != i)
    {
        mGameModeCmb->setCurrentIndex(i);
    }

    i = mStrengthCmb->findData(mSettings->mSolverStrength);
    if (i != -1 && mStrengthCmb->currentIndex() != i)
    {
        mStrengthCmb->setCurrentIndex(i);
    }

    mAutoCloseCb->setChecked(mSettings->mAutoClose);
    mAutoHintsCb->setChecked(mSettings->mAutoHints);

    mDelaySb->setValue(mSettings->mHintsDelay);

    mGamesListMaxCntSb->setValue(mSettings->mGamesListMaxCnt);
    mUserNameLe->setText(mSettings->mHighScoreUserName);
    if (mSettings->mHighScoreHandling == Settings::HIGHSCORE_PROMPT)
    {
        mUseHighscoresCb->setChecked(true);
        mHighscorePromptRb->setChecked(true);
    }
    else if(mSettings->mHighScoreHandling == Settings::HIGHSCORE_AUTO)
    {
        mUseHighscoresCb->setChecked(true);
        mHighscoreAutoRb->setChecked(true);
    }
    else if (mSettings->mHighScoreHandling == Settings::HIGHSCORE_NO)
    {
        mUseHighscoresCb->setChecked(false);
    }

    mCustomRowHColorCb->setChecked(mSettings->mCustomRowHColor);
    CustomRowHColorChangedSlot(mCustomRowHColorCb->checkState());

    if (sup)
    {
        SetSuppressSlots(false);
        ShowIndicatorsChangedSlot(mShowIndicatorsCb->checkState());
        UseHighscoresChangedSlot(mUseHighscoresCb->checkState());
    }
}
