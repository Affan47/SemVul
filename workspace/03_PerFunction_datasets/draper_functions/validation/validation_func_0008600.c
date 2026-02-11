OPL_SDL_Shutdown(void)
{
    Mix_HookMusic(NULL, NULL);

    if (sdl_was_initialized)
    {
        Mix_CloseAudio();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        OPL_Queue_Destroy(callback_queue);
        free(mix_buffer);
        sdl_was_initialized = 0;
    }


    if (callback_mutex != NULL)
    {
        SDL_DestroyMutex(callback_mutex);
        callback_mutex = NULL;
    }

    if (callback_queue_mutex != NULL)
    {
        SDL_DestroyMutex(callback_queue_mutex);
        callback_queue_mutex = NULL;
    }
}
