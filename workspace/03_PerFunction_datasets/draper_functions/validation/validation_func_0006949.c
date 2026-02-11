option(Fl_Option opt)
{
  if (!options_read_) {
    int tmp;
    {
      Fl_Preferences prefs(Fl_Preferences::SYSTEM, "fltk.org", "fltk");
      Fl_Preferences opt_prefs(prefs, "options");
      opt_prefs.get("ArrowFocus", tmp, 0);
      options_[OPTION_ARROW_FOCUS] = tmp;


      opt_prefs.get("VisibleFocus", tmp, 1);
      options_[OPTION_VISIBLE_FOCUS] = tmp;
      opt_prefs.get("DNDText", tmp, 1);
      options_[OPTION_DND_TEXT] = tmp;
      opt_prefs.get("ShowTooltips", tmp, 1);
      options_[OPTION_SHOW_TOOLTIPS] = tmp;
    }
    {

      Fl_Preferences prefs(Fl_Preferences::USER, "fltk.org", "fltk");
      Fl_Preferences opt_prefs(prefs, "options");
      opt_prefs.get("ArrowFocus", tmp, -1);
      if (tmp >= 0) options_[OPTION_ARROW_FOCUS] = tmp;


      opt_prefs.get("VisibleFocus", tmp, -1);
      if (tmp >= 0) options_[OPTION_VISIBLE_FOCUS] = tmp;
      opt_prefs.get("DNDText", tmp, -1);
      if (tmp >= 0) options_[OPTION_DND_TEXT] = tmp;
      opt_prefs.get("ShowTooltips", tmp, -1);
      if (tmp >= 0) options_[OPTION_SHOW_TOOLTIPS] = tmp;
    }
    {
    }
    options_read_ = 1;
  }
  if (opt<0 || opt>=OPTION_LAST)
    return false;
  return (bool)(options_[opt]!=0);
}
