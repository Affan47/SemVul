exposeEvent(XExposeEvent &event) {
    if (m_titlebar == event.window) {
        m_titlebar.clearArea(event.x, event.y, event.width, event.height);
    } else if (m_tab_container == event.window) {
        m_tab_container.clearArea(event.x, event.y, event.width, event.height);
    } else if (m_label == event.window) {
        m_label.clearArea(event.x, event.y, event.width, event.height);
    } else if (m_handle == event.window) {
        m_handle.clearArea(event.x, event.y, event.width, event.height);
    } else if (m_grip_left == event.window) {
        m_grip_left.clearArea(event.x, event.y, event.width, event.height);
    } else if (m_grip_right == event.window) {
        m_grip_right.clearArea(event.x, event.y, event.width, event.height);
    } else {

        if (m_tab_container.tryExposeEvent(event))
            return;


        FbTk::CompareEqual_base<FbTk::FbWindow, Window> compare(&FbTk::FbWindow::window,
                                                                event.window);

        ButtonList::iterator it = find_if(m_buttons_left.begin(),
                                          m_buttons_left.end(),
                                          compare);
        if (it != m_buttons_left.end()) {
            (*it)->exposeEvent(event);
            return;
        }

        it = find_if(m_buttons_right.begin(),
                     m_buttons_right.end(),
                     compare);

        if (it != m_buttons_right.end())
            (*it)->exposeEvent(event);
    }

}
