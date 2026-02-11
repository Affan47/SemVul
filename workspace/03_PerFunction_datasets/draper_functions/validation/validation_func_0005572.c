jshInputThread() {
  while (isInitialised) {

    bool shortSleep = false;

    if (execInfo.execute & EXEC_CTRL_C_WAIT)
      execInfo.execute = (execInfo.execute & ~EXEC_CTRL_C_WAIT) | EXEC_INTERRUPTED;
    if (execInfo.execute & EXEC_CTRL_C)
      execInfo.execute = (execInfo.execute & ~EXEC_CTRL_C) | EXEC_CTRL_C_WAIT;

    while (kbhit()) {
      int ch = getch();
      if (ch<0) break;
      jshPushIOCharEvent(EV_USBSERIAL, (char)ch);
    }

    if (jshGetEventsUsed() < IOBUFFERMASK/2) {
      int i;
      for (i=0;i<=EV_DEVICE_MAX;i++) {
        if (ioDevices[i]) {
          char buf[32];

          int bytes = (int)read(ioDevices[i], buf, sizeof(buf));
          if (bytes>0) {

            jshPushIOCharEvents(i, buf, (unsigned int)bytes);
            shortSleep = true;
          }
        }
      }
    }

    IOEventFlags device = jshGetDeviceToTransmit();
    while (device != EV_NONE) {
      char ch = (char)jshGetCharToTransmit(device);

      if (ioDevices[device]) {
        write(ioDevices[device], &ch, 1);
        shortSleep = true;
      }
      device = jshGetDeviceToTransmit();
    }


#ifdef SYSFS_GPIO_DIR
    Pin pin;
    for (pin=0;pin<JSH_PIN_COUNT;pin++)
      if (gpioShouldWatch[pin]) {
        shortSleep = true;
        bool state = jshPinGetValue(pin);
        if (state != gpioLastState[pin]) {
          jshPushIOEvent(pinToEVEXTI(pin) | (state?EV_EXTI_IS_HIGH:0), jshGetSystemTime());
          gpioLastState[pin] = state;
        }
      }
#endif

    usleep(shortSleep ? 1000 : 50000);
  }
}
