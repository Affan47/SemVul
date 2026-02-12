void Display::slotHelperFinished(Auth::HelperExitStatus status) {


        if (status != Auth::HELPER_AUTH_ERROR)
            stop();
    }
