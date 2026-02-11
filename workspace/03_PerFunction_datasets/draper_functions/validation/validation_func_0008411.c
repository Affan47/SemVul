TXT_SetWidgetBG(TXT_UNCAST_ARG(widget))
{
    TXT_CAST_ARG(txt_widget_t, widget);

    if (widget->focused)
    {
        TXT_BGColor(TXT_COLOR_GREY, 0);
    }
    else if (TXT_HoveringOverWidget(widget))
    {
        TXT_BGColor(TXT_HOVER_BACKGROUND, 0);
    }
    else
    {

    }
}
