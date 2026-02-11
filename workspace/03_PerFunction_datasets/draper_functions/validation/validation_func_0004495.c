setT60( StkFloat T60 )
{
  for ( int i=0; i<4; i++ )
    combCoefficient_[i] = pow(10.0, (-3.0 * combDelays_[i].getDelay() / (T60 * Stk::sampleRate())));
}
