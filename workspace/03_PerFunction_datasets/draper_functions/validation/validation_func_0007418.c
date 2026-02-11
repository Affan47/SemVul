setFrequency(StkFloat frequency)
{
  lastFrequency_ = frequency;
  if ( lastFrequency_ <= 0.0 ) {
    errorString_ << "Clarinet::setFrequency: parameter is less than or equal to zero!";
    handleError( StkError::WARNING );
    lastFrequency_ = 220.0;
  }


  lastLength_ = Stk::sampleRate() / lastFrequency_;
  StkFloat delay = (lastLength_ / detuning_) - 0.5;
  if ( delay <= 0.0 ) delay = 0.3;
  else if ( delay > length_ ) delay = length_;
  delayLine_.setDelay( delay );

  delay = (lastLength_ * detuning_) - 0.5;
  if ( delay <= 0.0 ) delay = 0.3;
  else if ( delay > length_ ) delay = length_;
  delayLine2_.setDelay( delay );

  loopGain_ = baseLoopGain_ + (frequency * 0.000005);
  if ( loopGain_ > 1.0 ) loopGain_ = 0.99999;
}
