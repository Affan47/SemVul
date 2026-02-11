move(int x, int y) {
    if (x == this->x() && y == this->y())
        return;

    menu.window.move(x, y);

    menu.title.parentMoved();
    menu.frame.parentMoved();

    if (!isVisible())
        return;

    if (alpha() < 255)
        clearWindow();

    if (m_which_sub != -1)
        drawSubmenu(m_which_sub);
}
