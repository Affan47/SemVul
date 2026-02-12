int wm_SemInit(wm_Sem *s){


        *s = dispatch_semaphore_create(0);
        if (*s == NULL)
            return MQTT_CODE_ERROR_MEMORY;
        if (dispatch_semaphore_signal(*s) < 0) {
            dispatch_release(*s);
            return MQTT_CODE_ERROR_SYSTEM;
        }

        return 0;
    }
