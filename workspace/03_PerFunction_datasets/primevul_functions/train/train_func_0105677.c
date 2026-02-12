GfxState *GfxState::restore()
{
    GfxState *oldState;

    if (saved) {
        oldState = saved;


        oldState->path = path;
        oldState->curX = curX;
        oldState->curY = curY;
        oldState->lineX = lineX;
        oldState->lineY = lineY;

        path = nullptr;
        saved = nullptr;
        delete this;

    } else {
        oldState = this;
    }

    return oldState;
}
