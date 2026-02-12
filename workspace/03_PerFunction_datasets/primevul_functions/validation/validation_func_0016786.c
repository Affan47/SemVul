void APar_ShowMPEG4VisualProfileInfo(TrackInfo *track_info) {
  fprintf(stdout, "  MPEG-4 Visual ");
  uint8_t mp4v_profile = 0;
  if (movie_info.contains_iods) {
    mp4v_profile = iods_info.video_profile_level;
  } else {
    mp4v_profile = track_info->m4v_profile;
  }


  if (mp4v_profile == 0x01) {
    fprintf(stdout, "Simple Profile, Level 1");
  } else if (mp4v_profile == 0x02) {
    fprintf(stdout, "Simple Profile, Level 2");
  } else if (mp4v_profile == 0x03) {
    fprintf(stdout,
            "Simple Profile, Level 3");

  } else if (mp4v_profile == 0x08) {
    fprintf(stdout, "Simple Profile, Level 0");


  } else if (mp4v_profile == 0x10) {
    fprintf(stdout, "Simple Scalable Profile, Level 0");
  } else if (mp4v_profile == 0x11) {
    fprintf(stdout, "Simple Scalable Profile, Level 1");
  } else if (mp4v_profile == 0x12) {
    fprintf(stdout, "Simple Scalable Profile, Level 2");


  } else if (mp4v_profile == 0x21) {
    fprintf(stdout, "Core Profile, Level 1");
  } else if (mp4v_profile == 0x22) {
    fprintf(stdout, "Core Profile, Level 2");


  } else if (mp4v_profile == 0x32) {
    fprintf(stdout, "Main Profile, Level 2");
  } else if (mp4v_profile == 0x33) {
    fprintf(stdout, "Main Profile, Level 3");
  } else if (mp4v_profile == 0x34) {
    fprintf(stdout, "Main Profile, Level 4");


  } else if (mp4v_profile == 0x42) {
    fprintf(stdout, "N-bit Profile, Level 2");


  } else if (mp4v_profile == 0x51) {
    fprintf(stdout, "Scalable Texture Profile, Level 1");


  } else if (mp4v_profile == 0x61) {
    fprintf(stdout, "Simple Face Animation, Level 1");
  } else if (mp4v_profile == 0x62) {
    fprintf(stdout, "Simple Face Animation, Level 2");

  } else if (mp4v_profile == 0x63) {
    fprintf(stdout, "Simple FBA Profile, Level 1");
  } else if (mp4v_profile == 0x64) {
    fprintf(stdout, "Simple FBA Profile, Level 2");


  } else if (mp4v_profile == 0x71) {
    fprintf(stdout, "Basic Animated Texture Profile, Level 1");
  } else if (mp4v_profile == 0x72) {
    fprintf(stdout, "Basic Animated Texture Profile, Level 2");


  } else if (mp4v_profile == 0x81) {
    fprintf(stdout, "Hybrid Profile, Level 1");
  } else if (mp4v_profile == 0x82) {
    fprintf(stdout, "Hybrid Profile, Level 2");


  } else if (mp4v_profile == 0x91) {
    fprintf(stdout, "Advanced Real Time Simple Profile, Level 1");
  } else if (mp4v_profile == 0x92) {
    fprintf(stdout, "Advanced Real Time Simple Profile, Level 2");
  } else if (mp4v_profile == 0x93) {
    fprintf(stdout, "Advanced Real Time Simple Profile, Level 3");
  } else if (mp4v_profile == 0x94) {
    fprintf(stdout, "Advanced Real Time Simple Profile, Level 4");


  } else if (mp4v_profile == 0xA1) {
    fprintf(stdout, "Core Scalable Profile, Level 1");
  } else if (mp4v_profile == 0xA2) {
    fprintf(stdout, "Core Scalable Profile, Level 2");
  } else if (mp4v_profile == 0xA3) {
    fprintf(stdout, "Core Scalable Profile, Level 3");


  } else if (mp4v_profile == 0xB1) {
    fprintf(stdout, "Advanced Coding Efficiency Profile, Level 1");
  } else if (mp4v_profile == 0xB2) {
    fprintf(stdout, "Advanced Coding Efficiency Profile, Level 2");
  } else if (mp4v_profile == 0xB3) {
    fprintf(stdout, "Advanced Coding Efficiency Profile, Level 3");
  } else if (mp4v_profile == 0xB4) {
    fprintf(stdout, "Advanced Coding Efficiency Profile, Level 4");


  } else if (mp4v_profile == 0xC1) {
    fprintf(stdout, "Advanced Core Profile, Level 1");
  } else if (mp4v_profile == 0xC2) {
    fprintf(stdout, "Advanced Core Profile, Level 2");


  } else if (mp4v_profile == 0xD1) {
    fprintf(stdout, "Advanced Scalable Texture, Level 1");
  } else if (mp4v_profile == 0xD2) {
    fprintf(stdout, "Advanced Scalable Texture, Level 2");
  } else if (mp4v_profile == 0xD2) {
    fprintf(stdout, "Advanced Scalable Texture, Level 3");


  } else if (mp4v_profile == 0xE1) {
    fprintf(stdout, "Simple Studio Profile, Level 1");
  } else if (mp4v_profile == 0xE2) {
    fprintf(stdout, "Simple Studio Profile, Level 2");
  } else if (mp4v_profile == 0xE3) {
    fprintf(stdout, "Simple Studio Profile, Level 3");
  } else if (mp4v_profile == 0xE4) {
    fprintf(stdout, "Simple Studio Profile, Level 4");

  } else if (mp4v_profile == 0xE5) {
    fprintf(stdout, "Core Studio Profile, Level 1");
  } else if (mp4v_profile == 0xE6) {
    fprintf(stdout, "Core Studio Profile, Level 2");
  } else if (mp4v_profile == 0xE7) {
    fprintf(stdout, "Core Studio Profile, Level 3");
  } else if (mp4v_profile == 0xE8) {
    fprintf(stdout, "Core Studio Profile, Level 4");


  } else if (mp4v_profile == 0xF0) {
    fprintf(stdout, "Advanced Simple Profile, Level 0");
  } else if (mp4v_profile == 0xF1) {
    fprintf(stdout, "Advanced Simple Profile, Level 1");
  } else if (mp4v_profile == 0xF2) {
    fprintf(
        stdout,
        "Advanced Simple Profile, Level 2");


  } else if (mp4v_profile == 0xF3) {
    fprintf(stdout, "Advanced Simple Profile, Level 3");
  } else if (mp4v_profile == 0xF4) {
    fprintf(stdout, "Advanced Simple Profile, Level 4");
  } else if (mp4v_profile == 0xF5) {
    fprintf(stdout, "Advanced Simple Profile, Level 5");


  } else if (mp4v_profile == 0xF7) {
    fprintf(stdout, "Advanced Simple Profile, Level 3b");

  } else if (mp4v_profile == 0xF7) {
    fprintf(stdout, "Fine Granularity Scalable Profile/Level 0");
  } else if (mp4v_profile == 0xF7) {
    fprintf(stdout, "Fine Granularity Scalable Profile/Level 1");
  } else if (mp4v_profile == 0xF7) {
    fprintf(stdout, "Fine Granularity Scalable Profile/Level 2");
  } else if (mp4v_profile == 0xF7) {
    fprintf(stdout, "Fine Granularity Scalable Profile/Level 3");
  } else if (mp4v_profile == 0xF7) {
    fprintf(stdout, "Fine Granularity Scalable Profile/Level 4");
  } else if (mp4v_profile == 0xF7) {
    fprintf(stdout, "Fine Granularity Scalable Profile/Level 5");


  } else {
    fprintf(stdout, "Unknown profile: 0x%X", mp4v_profile);
  }
  return;
}
