HousePlacidus()
{
  int i;

  chouse[1] = Mod(is.Asc-is.rSid);
  chouse[4] = Mod(is.MC+rDegHalf-is.rSid);
  chouse[5] = CuspPlacidus(30.0, 3.0, fFalse) + rDegHalf;
  chouse[6] = CuspPlacidus(60.0, 1.5, fFalse) + rDegHalf;
  chouse[2] = CuspPlacidus(120.0, 1.5, fTrue);
  chouse[3] = CuspPlacidus(150.0, 3.0, fTrue);
  for (i = 1; i <= cSign; i++) {
    if (i <= 6)
      chouse[i] = Mod(chouse[i]+is.rSid);
    else
      chouse[i] = Mod(chouse[i-6]+rDegHalf);
  }
}
