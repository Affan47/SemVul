onAlphaChanged(WindowEventArgs& e)
    {

        if (d_dragging)
        {
            d_storedAlpha = d_alpha;
            d_alpha = d_dragAlpha;
        }

        Window::onAlphaChanged(e);
    }
