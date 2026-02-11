WidgetActivated( Widget *widget, Window *win ) {
  GUI_Status rc = GUI_OK;

  switch ( widget->ID() ) {
  case CH_BUTTON_REPAIR: {
    ULWNode *n = static_cast<ULWNode *>(listwidget->Selected());
    if ( n ) {
      Unit *u = n->unit;
      if ( u->GroupSize() < MAX_GROUP_SIZE ) {
        string repmsg;
        repmsg = StringUtil::strprintf( MSG(MSG_ASK_REPAIR), u->Name() );
        repmsg = StringUtil::strprintf( repmsg, CRYSTALS_REPAIR );

        if ( c->Crystals() >= CRYSTALS_REPAIR ) {
          string buttons;
          buttons.append( MSG(MSG_B_REPAIR) );
          buttons += '|';
          buttons.append( MSG(MSG_B_CANCEL) );
          DialogWindow *reqwin =
            new DialogWindow( NULL, repmsg, buttons, 0, 0, view );
          reqwin->SetButtonID( 0, CH_BUTTON_REPAIR_CONFIRM );
          reqwin->SetButtonHook( 0, this );
        } else new NoteWindow( MSG(MSG_ERR_NO_CRYSTALS), repmsg, WIN_CLOSE_ESC, view );
      }
    }
    break; }
  case CH_BUTTON_BUILD:
    SwitchMode( (Mode() == CW_MODE_NORMAL) ? CW_MODE_PRODUCTION : CW_MODE_NORMAL );
    break;

  case CH_BUTTON_REPAIR_CONFIRM: {
    Audio::PlaySfx( Audio::SND_GAM_REPAIR, 0 );
    Unit *u = static_cast<ULWNode *>(listwidget->Selected())->unit;
    c->SetCrystals( c->Crystals() - CRYSTALS_REPAIR );
    if ( Gam->GetMission()->GetHistory() )
      Gam->GetMission()->GetHistory()->RecordUnitEvent( *u, History::HIST_UEVENT_REPAIR );

    u->Repair();
    listwidget->Draw();
    DrawCrystals();
    Show();
    rc = GUI_CLOSE;
    break; }

  case CH_LIST_UNITS: {


    ULWNode *node = static_cast<ULWNode *>(
                    static_cast<ListWidget *>(widget)->Selected()
                    );

    if ( node != last_selected ) {
      short uid = -1;
      if ( node ) uid = node->type->ID();
      DrawBack( unitinfo );
      UnitInfoWindow::DrawUnitInfo( uid, &Gam->GetMission()->GetUnitSet(),
                      &Gam->GetMission()->GetTerrainSet(), this, unitinfo );
      win->Show( unitinfo );
      last_selected = node;
    } else if ( node ) rc = SelectNode( node );
    break; }
  }

  return rc;
}
