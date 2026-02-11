update_punct_key()
{
    string punct_switch("ControlComma");
    punct_switch = m_config.get(CONFIG_KEYBOARD_PUNCT_SWITCH, punct_switch);
    if (punct_switch == "ControlComma") {
        m_hotkey_profile->setPunctSwitchKey(CKeyEvent(IM_VK_COMMA, 0, IM_CTRL_MASK));
    } else if (punct_switch == "ControlPeriod") {
        m_hotkey_profile->setPunctSwitchKey(CKeyEvent(IM_VK_PERIOD, 0, IM_CTRL_MASK));
    }
}
