ZMpvAxisAngleRep( const HepAxisAngle & aa, double array[] ) {

  register double sinDelta = std::sin( aa.delta() );
  register double cosDelta = std::cos( aa.delta() );
  register double oneMinusCosDelta = 1.0 - cosDelta;

  register double uX = aa.getAxis().getX();
  register double uY = aa.getAxis().getY();
  register double uZ = aa.getAxis().getZ();

  array[0] = oneMinusCosDelta * uX * uX  +  cosDelta;
  array[1] = oneMinusCosDelta * uX * uY  -  sinDelta * uZ;
  array[2] = oneMinusCosDelta * uX * uZ  +  sinDelta * uY;

  array[3] = oneMinusCosDelta * uY * uX  +  sinDelta * uZ;
  array[4] = oneMinusCosDelta * uY * uY  +  cosDelta;
  array[5] = oneMinusCosDelta * uY * uZ  -  sinDelta * uX;

  array[6] = oneMinusCosDelta * uZ * uX  -  sinDelta * uY;
  array[7] = oneMinusCosDelta * uZ * uY  +  sinDelta * uX;
  array[8] = oneMinusCosDelta * uZ * uZ  +  cosDelta;

}
