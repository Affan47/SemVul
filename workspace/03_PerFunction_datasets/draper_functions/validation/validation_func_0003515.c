CheckBegin()
    {
        if(!audfp)
        {
            unlink(AUDIO_FN.c_str());
            mknod(AUDIO_FN.c_str(), S_IFIFO|0666, 0);
        }

        if(!vidfp)
        {

            setenv("LD_PRELOAD", "", 1);
            vidfp = popen(GetMEncoderCommand().c_str(), "w");
            if(!vidfp)
            {
                perror("Launch failed");
            }
            else
            {
                fcntl(fileno(vidfp), F_SETFL, O_WRONLY | O_NONBLOCK);
            }
        }

        if(!audfp)
        {
        Retry:
            audfp = fopen(AUDIO_FN.c_str(), "wb");

            if(!audfp)
            {
                perror(AUDIO_FN.c_str());
                if(errno == ESTALE) goto Retry;
            }
            else
            {
                fcntl(fileno(audfp), F_SETFL, O_WRONLY | O_NONBLOCK);
            }
        }
    }
