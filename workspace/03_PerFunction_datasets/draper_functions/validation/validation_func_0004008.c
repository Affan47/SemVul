loadGraphicsResources (void)
{
    float screenScale = System::getInstance ().getScreenScaleFactor ();

    uint16_t nameY = k_SeparationBetweenPlayerAndLabel;
    m_Background.reset (
            Surface::fromFile (File::getGraphicsFilePath ("menuBackground.png")));
    {
        std::auto_ptr<Surface> winner (
                Surface::fromFile (File::getGraphicsFilePath (getWinnerName () + ".png")));
        uint16_t winnerY = m_Background->getHeight () / 2 -
                           winner->getHeight () / 2;
        winner->blit (m_Background->getWidth () / 2 - winner->getWidth () / 2,
                      winnerY, m_Background->toSDLSurface ());

        std::auto_ptr<Surface> YouWin (
                Surface::fromFile (File::getGraphicsFilePath ("winner.png")));

        YouWin->blit (m_Background->getWidth () / 2 - YouWin->getWidth () / 2,
                      m_Background->getHeight () / 2 -
                      winner->getHeight () / 2 -
                      YouWin->getHeight () -
                      static_cast<uint16_t> (k_SeparationBetweenPlayerAndLabel *
                                             screenScale),
                      m_Background->toSDLSurface ());

        nameY += winnerY + winner->getHeight ();
    }
    m_Background->resize (screenScale);
    {
        std::auto_ptr<Font> font (
                Font::fromFile (File::getFontFilePath ("fontMenu")));

        font->write (getWinnerName (),
                     m_Background->getWidth () / 2 -
                     font->getTextWidth (getWinnerName ()) / 2,
#if defined (IS_GP2X_HOST)
                     static_cast<uint16_t> (nameY),
#else
                     static_cast<uint16_t> (nameY * screenScale),
#endif
                     m_Background->toSDLSurface ());
    }
}
