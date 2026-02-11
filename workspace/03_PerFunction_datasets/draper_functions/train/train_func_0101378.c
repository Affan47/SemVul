setDormant()
{
    if (!mStopButton->text().contains("Stop", Qt::CaseSensitive))
    {
    	stopClickedSlot();
    }

	mMips->setActive(false);
}
