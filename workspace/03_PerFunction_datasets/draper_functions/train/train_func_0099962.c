setFromString(char const *strval) {
    vector<string> val;
    StringUtil::stringtok(val, strval);

    m_value.clear();

    std::string v;
    for (size_t i = 0; i < val.size(); i++) {
        v = FbTk::StringUtil::toLower(val[i]);
        if (v == "maximize")
            m_value.push_back(WinButton::MAXIMIZE);
        else if (v == "minimize")
            m_value.push_back(WinButton::MINIMIZE);
        else if (v == "shade")
            m_value.push_back(WinButton::SHADE);
        else if (v == "stick")
            m_value.push_back(WinButton::STICK);
        else if (v == "menuicon")
            m_value.push_back(WinButton::MENUICON);
        else if (v == "close")
            m_value.push_back(WinButton::CLOSE);
        else if (v == "lhalf")
            m_value.push_back(WinButton::LEFT_HALF);
        else if (v == "rhalf")
            m_value.push_back(WinButton::RIGHT_HALF);
    }
}
