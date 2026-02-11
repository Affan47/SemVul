checkForRemoveStateKey (uint32_t key)
{
    if ( !m_StateAlreadyRemoved &&
#if defined IS_GP2X_HOST
        (key == GP2X_BUTTON_START ||
         key == GP2X_BUTTON_SELECT ||
         key == GP2X_BUTTON_B ||
         key == GP2X_BUTTON_X)
#else
         (key == SDLK_RETURN ||
          key == SDLK_ESCAPE)
#endif
         )
    {
        System::getInstance ().removeActiveState ();
        m_StateAlreadyRemoved = true;
    }
}
