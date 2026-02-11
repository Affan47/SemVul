stopDemoMode()
{
    TimerState = Stop;
    calculateNewGame();
    setStatusText(i18n("Now it is you again."));

    emit demoModeChanged(false);
    emit gameCalculated();
}
