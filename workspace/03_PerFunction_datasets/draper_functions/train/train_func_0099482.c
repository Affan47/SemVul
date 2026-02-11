event_filter( SDL_Event &event, Window *window ) {
  GUI_Status rc = GUI_OK;

  if ( event.type == SDL_KEYDOWN ) {
    rc = GUI_NONE;

    switch ( event.key.keysym.sym ) {
    case SDLK_F11:
      Audio::ToggleSfxState();
      break;
    default:
      rc = GUI_OK;
    }
  } else if ( event.type == SDL_QUIT ) rc = GUI_QUIT;

  return rc;
}
