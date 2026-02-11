duplicate(ball * pack)
{
  kball * output = new kball(pack);
  output->setcenter(center);
  output->setvelocity(velocity);
  output->setboundary(boundary);
  return output;
}
