isModal() {
    if (!client())
        return false;

    if (getState() & WinStateModal)
        return true;

    MwmHints *mwmHints = client()->mwmHints();
    if (mwmHints && (mwmHints->flags & MWM_HINTS_INPUT_MODE))
        if (mwmHints->input_mode != MWM_INPUT_MODELESS)
            return true;

    if (hasModal())
        return true;

    return false;
}
