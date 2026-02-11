click(int button, int time, unsigned int mods) {

        Remember::instance().checkReload();
        if (FbMenu::window() != 0) {
            if (isSelected()) {
                Remember::instance().forgetAttrib(FbMenu::window()->winClient(), m_attrib);
            } else {
                Remember::instance().rememberAttrib(FbMenu::window()->winClient(), m_attrib);
            }
        }
        Remember::instance().save();
        FbTk::MenuItem::click(button, time, mods);
    }
