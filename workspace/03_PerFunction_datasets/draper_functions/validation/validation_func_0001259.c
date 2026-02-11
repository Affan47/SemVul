sizeSelf(void)
    {
        Size textSize(getTextSize());

        setSize(
            UVector2(cegui_absdim(textSize.d_width),
                     cegui_absdim(textSize.d_height)));
    }
