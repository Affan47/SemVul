draw ()
{
  char buf [250], buf2 [10];
  int timeroff = 100 * timestep, timerdelay = 300 * timestep, timerlag = 20 * timestep;
  if (timer >= 0 && timer <= timeroff - 20)
  {
    font1->drawTextCentered (0, 4, -2, name, &textcolor);
  }
  else if (timer > timeroff && timer <= timeroff + timerdelay - timerlag)
  {
    font1->drawTextCentered (0, 7, -2.5, "FIRSTLY, HAVE A LOOK AT YOUR MISSILES:", &textcolor);
    key2string (key_selectmissile, buf2);
    sprintf (buf, "PRESS '%s' TO SWITCH BETWEEN", buf2);
    font1->drawTextCentered (0, 6, -2.5, buf, &textcolor);
    font1->drawTextCentered (0, 5, -2.5, "AGM (AIR-GROUND-MISSILE) AND DF (DUMB FIRE)", &textcolor);
  }
  else if (timer > timerdelay + timeroff && timer <= timeroff + 2 * timerdelay - timerlag)
  {
    font1->drawTextCentered (0, 7, -2.5, "LET'S USE THE AGM: AS SOON AS THE TARGET", &textcolor);
    font1->drawTextCentered (0, 6, -2.5, "IS LOCKED (YELLOW), SHOOT THE AGM AT ANY", &textcolor);
    font1->drawTextCentered (0, 5, -2.5, "DIRECTION AND WATCH WHERE IT GOES.", &textcolor);
  }
  else if (timer > 2 * timerdelay + timeroff && timer <= timeroff + 3 * timerdelay - timerlag)
  {
    font1->drawTextCentered (0, 7, -2.5, "THEN TRY A DF MISSILE BUT CAREFUL:", &textcolor);
    font1->drawTextCentered (0, 6, -2.5, "IT IS QUITE 'DUMB' AND WILL FLY STRAIGHT AHEAD.", &textcolor);
  }
  else if (timer > 3 * timerdelay + timeroff && timer <= timeroff + 4 * timerdelay - timerlag)
  {
    font1->drawTextCentered (0, 6, -2.5, "HOWEVER, DF MISSILES WILL CAUSE MUCH MORE DAMAGE", &textcolor);
  }
  else if (timer > 4 * timerdelay + timeroff && timer <= timeroff + 5 * timerdelay - timerlag)
  {
    font1->drawTextCentered (0, 6, -2.5, "NOW, BLOW UP THE TWO TANKS", &textcolor);
  }
}
