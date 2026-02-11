isEditable() const
{
    RenderText *textRenderer = 0;
    if (isText()) {
        textRenderer = static_cast<RenderText *>(const_cast<RenderObject *>(this));
    }

    return style()->visibility() == VISIBLE &&
        element() && element()->isContentEditable() &&
        ((isBlockFlow() && !firstChild()) ||
        isReplaced() ||
        isBR() ||
        (textRenderer && textRenderer->firstTextBox()));
}
