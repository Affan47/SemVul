GetSupportedState (Atom atom)
{
  if (atom == XA_NET_WM_STATE_FULLSCREEN)
    return wm_FULLSCREEN;

  if (atom == XA_NET_WM_STATE_ABOVE)
    return wm_ABOVE;

  if (atom == XA_NET_WM_STATE_STAYS_ON_TOP)
    return wm_STAYS_ON_TOP;

  if (atom==XA_NET_WM_STATE_BELOW)
    return wm_BELOW;

  return 0;
}
