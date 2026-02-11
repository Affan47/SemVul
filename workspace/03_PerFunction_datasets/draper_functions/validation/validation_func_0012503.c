adin_callback_file(SP16 *now, int len, Recog *recog)
{
  int count;
  int start;
  int w;

  start = 0;

  if (recog->jconf->input.speech_input == SP_MIC && speechlen == 0) {

    if (rewind_msec > 0 && !recog->adin->is_valid_data) {


      printf("disgard already recorded %d samples\n", len);
      return 0;
    }

    fprintf(stderr, "\r                    \r");
    if (rewind_msec > 0) {


      printf("buffered samples=%d\n", len);
      w = rewind_msec * sfreq / 1000;
      if (len > w) {
	start = len - w;
	len = w;
      } else {
	start = 0;
      }
      printf("will process from %d\n", start);
    }
  }


  if (speech_output == SPOUT_FILE && speechlen == 0) {
    if (continuous_segment) {
      if (use_raw) {
	sprintf(outpath, "%s.%04d.raw", filename, sid);
      } else {
	sprintf(outpath, "%s.%04d.wav", filename, sid);
      }
    }
    fprintf(stderr,"[%s]", outpath);
    if (access(outpath, F_OK) == 0) {
      if (access(outpath, W_OK) == 0) {
	fprintf(stderr, "(override)");
      } else {
	perror("adintool");
	return(-1);
      }
    }
    if (use_raw) {
      if ((fd = open(outpath, O_CREAT | O_RDWR
#ifdef O_BINARY
		     | O_BINARY
#endif
		     , 0644)) == -1) {
	perror("adintool");
	return -1;
      }
    } else {
      if ((fp = wrwav_open(outpath, sfreq)) == NULL) {
	perror("adintool");
	return -1;
      }
    }
    writing_file = TRUE;
  }


  if (use_raw) {
    count = wrsamp(fd, &(now[start]), len);
    if (count < 0) {
      perror("adinrec: cannot write");
      return -1;
    }
    if (count < len * sizeof(SP16)) {
      fprintf(stderr, "adinrec: cannot write more %d bytes\ncurrent length = %d\n", count, speechlen * sizeof(SP16));
      return -1;
    }
  } else {
    if (wrwav_data(fp, &(now[start]), len) == FALSE) {
      fprintf(stderr, "adinrec: cannot write\n");
      return -1;
    }
  }


  speechlen += len;


  if (recog->jconf->input.speech_input == SP_MIC) {
    if (speechlen > MAXSPEECHLEN - 16000) {
      recog->adin->rehash = TRUE;
    }
  }


  fprintf(stderr, ".");

  return(0);
}
