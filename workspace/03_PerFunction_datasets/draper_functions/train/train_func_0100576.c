OnIdle(wxIdleEvent &)
  {
    if (abs(pos - dpos) < 10e-6)


      return;


    pos += (dpos - pos) / 7;

    Refresh(false);

    wxMilliSleep(1000.0/FPS);
  }
