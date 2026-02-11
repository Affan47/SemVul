WidgetActivated( Widget *button, Window *win ) {

  switch ( button->ID() ) {
  case B_ID_EDIT: {
    TLWNode *n = static_cast<TLWNode *>( e_list->Selected() );
    if ( n ) {
      Event *e = (Event *)n->UserData();
      new EdEventGenericWindow( *e, mission, view );
    }
    break; }
  case B_ID_NEW:
    view->CloseWindow( win );
    new SelectEventWindow( mission, view );
    break;
  case B_ID_DELETE: {
    TLWNode *n = static_cast<TLWNode *>( e_list->Selected() );
    if ( n ) {
      Event *e = (Event *)n->UserData();

      n->Remove();
      delete n;
      e_list->Update();
      e_list->Draw();
      e_list->Show();

      mission.DeleteEvent( e );
    }
    break; }
  case B_ID_OK:
    view->CloseWindow( win );
    break;
  }

  return GUI_OK;
}
