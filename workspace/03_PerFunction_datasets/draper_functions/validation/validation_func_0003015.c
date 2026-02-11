UpdateModifierState(SDL_keysym *sym, int pressed)
{
    txt_modifier_t mod;

    switch (sym->sym)
    {
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            mod = TXT_MOD_SHIFT;
            break;

        case SDLK_LCTRL:
        case SDLK_RCTRL:
            mod = TXT_MOD_CTRL;
            break;

        case SDLK_LALT:
        case SDLK_RALT:
#if !SDL_VERSION_ATLEAST(1, 3, 0)
        case SDLK_LMETA:
        case SDLK_RMETA:
#endif
            mod = TXT_MOD_ALT;
            break;

        default:
            return;
    }

    if (pressed)
    {
        ++modifier_state[mod];
    }
    else
    {
        --modifier_state[mod];
    }
}
