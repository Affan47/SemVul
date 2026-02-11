render (SDL_Surface *screen)
{
    const float screenScale = System::getInstance ().getScreenScaleFactor ();
    Font *leftFont = m_FontNormal.get ();
    Font *rightFont = m_FontNormal.get ();

    if ( 0 == getSelectedCharacter () )
    {
        leftFont = m_FontSelected.get ();
    }
    else
    {
        rightFont = m_FontSelected.get ();
    }

    leftFont->write (k_CharacterNames[0],
                     m_Background->getWidth () / 2 -
                     static_cast<uint16_t> (screenScale * k_CharacterSeparation) -
                     leftFont->getTextWidth (k_CharacterNames[0]) / 2,
                     static_cast<uint16_t> (screenScale * k_NamesPositionY),
                     screen);
    rightFont->write (k_CharacterNames[1],
                     m_Background->getWidth () / 2 +
                     static_cast<uint16_t> (screenScale * k_CharacterSeparation) -
                     leftFont->getTextWidth (k_CharacterNames[1]) / 2,
                     static_cast<uint16_t> (screenScale * k_NamesPositionY),
                     screen);
}
