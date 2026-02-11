ui_install_mode(char *name, PFI proc, int type)
{
  if(uistate.mode_count >= MAXMODES) {
    OOGLError(1, "Motion-mode table full (max %d entries)", MAXMODES);
    uistate.mode_count = MAXMODES-1;
  }
  uistate.modenames[uistate.mode_count] = name;
  uistate.modes[uistate.mode_count] = proc;
  uistate.modetype[uistate.mode_count] = type;
  ++uistate.mode_count;

D1PRINT(("ui_install_mode: name=%s, proc=%x\n", name, proc));

}
