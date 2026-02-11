onAlphaChanged(WindowEventArgs& e)
{

    const size_t child_count = getChildCount();

    for (size_t i = 0; i < child_count; ++i)
    {
        if (d_children[i]->inheritsAlpha())
        {
            WindowEventArgs args(d_children[i]);
            d_children[i]->onAlphaChanged(args);
        }

    }

    invalidate();
    fireEvent(EventAlphaChanged, e, EventNamespace);
}
