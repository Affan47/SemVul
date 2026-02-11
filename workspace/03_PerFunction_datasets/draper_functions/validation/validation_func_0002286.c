checkForKey( const SDL_KeyboardEvent* key, int modifier, int num ) {
        return ( key->keysym.unicode == 'f' && (modifier & KMOD_SHIFT)  );
    }
