UserStats_add_download(UserStats* us, int bytes)
{
  time_t now;

  assert(us != NULL);

  if (us == NULL) {
    return;
  }


  time(&now);


  switch (now - us->lastDSQChange) {
    case 0: {
      us->downloadSpeedQueue[us->downloadSQP] += bytes;
      break;
    }
    case 2: {
      us->downloadSQP = (us->downloadSQP + 1) % 3;
      us->downloadSpeedQueue[us->downloadSQP] = 0;
    }
    case 1: {
      us->downloadSQP = (us->downloadSQP + 1) % 3;
      us->downloadSpeedQueue[us->downloadSQP] = bytes;
      break;
    }
    default: {
      us->downloadSpeedQueue[0] = us->downloadSpeedQueue[1] = us->downloadSpeedQueue[2] = 0;
      us->downloadSpeedQueue[us->downloadSQP] = bytes;
    }
  }


  us->totalDownloadedBytes += bytes;


  us->lastActivity = now;


  us->lastDSQChange = now;
}
