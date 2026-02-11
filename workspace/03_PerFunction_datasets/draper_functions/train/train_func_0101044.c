onKeyDown(KeyEventArgs& e)
{


    fireEvent(EventKeyDown, e, Window::EventNamespace);

    if (e.handled == 0 && hasInputFocus() && !isReadOnly())
    {
        WindowEventArgs args(this);
        switch (e.scancode)
        {
        case Key::LeftShift:
        case Key::RightShift:
            if (getSelectionLength() == 0)
                d_dragAnchorIdx = d_caratPos;
            break;

        case Key::Backspace:
            handleBackspace();
            break;

        case Key::Delete:
            handleDelete();
            break;

        case Key::Tab:
        case Key::Return:
        case Key::NumpadEnter:

            onTextAcceptedEvent(args);
            break;

        case Key::ArrowLeft:
            if (e.sysKeys & Control)
                handleWordLeft(e.sysKeys);
            else
                handleCharLeft(e.sysKeys);
            break;

        case Key::ArrowRight:
            if (e.sysKeys & Control)
                handleWordRight(e.sysKeys);
            else
                handleCharRight(e.sysKeys);
            break;

        case Key::Home:
            handleHome(e.sysKeys);
            break;

        case Key::End:
            handleEnd(e.sysKeys);
            break;


        default:
            return;
        }

        ++e.handled;
    }

}
