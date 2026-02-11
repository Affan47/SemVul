setModeGain(unsigned int modeIndex, StkFloat gain)
{
  if ( modeIndex >= nModes_ ) {
    errorString_ << "Modal::setModeGain: modeIndex parameter is greater than number of modes!";
    handleError( StkError::WARNING );
    return;
  }

  filters_[modeIndex]->setGain(gain);
}
