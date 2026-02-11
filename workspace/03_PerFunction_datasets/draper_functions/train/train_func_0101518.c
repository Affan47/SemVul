changeHideShowState()
{
  if ( mayBeHide() ){
    undock();
    return;
  }

  if ( mayBeShow() ){
    if ( manager->main->inherits("K3DockMainWindow") ){
      ((K3DockMainWindow*)manager->main)->makeDockVisible(this);
    } else {
      makeDockVisible();
    }
  }
}
