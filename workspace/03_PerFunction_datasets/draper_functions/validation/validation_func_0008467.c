setArmed(bool armed, bool mouseDown) {
    if (armed != fArmed) {
        fArmed = armed;
        repaint();
        if (fPopup) {
            if (fArmed)
                popup(mouseDown);
            else
                popdown();
        }
    }
}
