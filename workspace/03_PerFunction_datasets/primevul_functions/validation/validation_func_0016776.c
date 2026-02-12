void APar_ShowObjectProfileInfo(uint8_t track_type, TrackInfo *track_info) {
  if (track_info->contains_esds) {
    switch (track_info->ObjectTypeIndication) {

    case 0x01:
    case 0x02: {
      fprintf(stdout, "  MPEG-4 Systems (BIFS/ObjDesc)");
      break;
    }
    case 0x03: {
      fprintf(stdout, "  Interaction Stream");
      break;
    }
    case 0x04: {
      fprintf(stdout, "  MPEG-4 Systems Extended BIFS");
      break;
    }
    case 0x05: {
      fprintf(stdout, "  MPEG-4 Systems AFX");
      break;
    }
    case 0x06: {
      fprintf(stdout, "  Font Data Stream");
      break;
    }
    case 0x08: {
      fprintf(stdout, "  Synthesized Texture Stream");
      break;
    }
    case 0x07: {
      fprintf(stdout, "  Streaming Text Stream");
      break;
    }

    case 0x20: {
      APar_ShowMPEG4VisualProfileInfo(track_info);
      break;
    }

    case 0x40: {
      APar_ShowMPEG4AACProfileInfo(track_info);
      break;
    }


    case 0x60: {
      fprintf(stdout,
              "  MPEG-2 Visual Simple Profile");

      break;
    }
    case 0x61: {
      fprintf(stdout, "  MPEG-2 Visual Main Profile");

      break;
    }
    case 0x62: {
      fprintf(
          stdout,
          "  MPEG-2 Visual SNR Profile");
      break;
    }
    case 0x63: {
      fprintf(stdout,
              "  MPEG-2 Visual Spatial Profile");

      break;
    }
    case 0x64: {
      fprintf(stdout, "  MPEG-2 Visual High Profile");

      break;
    }
    case 0x65: {
      fprintf(stdout, "  MPEG-2 Visual 4:2:2 Profile");

      break;
    }
    case 0x66: {
      fprintf(
          stdout,
          "  MPEG-2 AAC Main Profile");
      break;
    }
    case 0x67: {
      fprintf(stdout,
              "  MPEG-2 AAC Low Complexity Profile");

      break;
    }
    case 0x68: {
      fprintf(
          stdout,
          "  MPEG-2 AAC Scaleable Sample Rate Profile");


      break;
    }
    case 0x69: {
      fprintf(stdout, "  MPEG-2 Audio");
      break;
    }
    case 0x6A: {
      fprintf(stdout, "  MPEG-1 Visual");
      break;
    }
    case 0x6B: {
      fprintf(stdout, "  MPEG-1 Audio");
      break;
    }
    case 0x6C: {
      fprintf(stdout, "  JPEG");
      break;
    }
    case 0x6D: {
      fprintf(stdout, "  PNG");
      break;
    }
    case 0x6E: {
      fprintf(stdout, "  JPEG2000");
      break;
    }
    case 0xA0: {
      fprintf(stdout, "  3GPP2 EVRC Voice");
      break;
    }
    case 0xA1: {
      fprintf(stdout, "  3GPP2 SMV Voice");
      break;
    }
    case 0xA2: {
      fprintf(
          stdout,
          "  3GPP2 Compact Multimedia Format");
      break;
    }


    case 0xE1: {
      fprintf(stdout,
              "  3GPP2 QCELP (14K Voice)");
      break;
    }


    default: {


      if (movie_info.contains_iods && iods_info.audio_profile == 0xFE) {
        fprintf(stdout,
                "  Private user object: 0x%X",
                track_info->ObjectTypeIndication);
      } else {
        fprintf(
            stdout,
            "  Object Type Indicator: 0x%X  Description Ojbect Type ID: 0x%X\n",
            track_info->ObjectTypeIndication,
            track_info->descriptor_object_typeID);
      }
      break;
    }
    }

  } else if (track_type == AVC1_TRACK) {


    switch (track_info->profile) {
    case 66: {
      fprintf(stdout, "  AVC Baseline Profile");
      break;
    }
    case 77: {
      fprintf(stdout, "  AVC Main Profile");
      break;
    }
    case 88: {
      fprintf(stdout, "  AVC Extended Profile");
      break;
    }
    case 100: {
      fprintf(stdout, "  AVC High Profile");
      break;
    }
    case 110: {
      fprintf(stdout, "  AVC High 10 Profile");
      break;
    }
    case 122: {
      fprintf(stdout, "  AVC High 4:2:2 Profile");
      break;
    }
    case 144: {
      fprintf(stdout, "  AVC High 4:4:4 Profile");
      break;
    }
    default: {
      fprintf(stdout, "  Unknown Profile: %u", track_info->profile);
      break;
    }
    }


    if (track_info->level > 0) {
      switch (track_info->level) {
      case 10:
      case 20:
      case 30:
      case 40:
      case 50: {
        fprintf(stdout, ",  Level %u", track_info->level / 10);
        break;
      }
      case 11:
      case 12:
      case 13:
      case 21:
      case 22:
      case 31:
      case 32:
      case 41:
      case 42:
      case 51: {
        fprintf(stdout,
                ",  Level %u.%u",
                track_info->level / 10,
                track_info->level % 10);
        break;
      }
      default: {
        fprintf(stdout,
                ", Unknown level %u.%u",
                track_info->level / 10,
                track_info->level % 10);
      }

      }
    }
  } else if (track_type == S_AMR_TRACK) {
    char amr_modes[500] = {};
    if (track_info->track_codec == 0x73616D72 ||
        track_info->track_codec == 0x73617762) {
      if (track_info->amr_modes & 0x0001)
        mem_append("0", amr_modes);
      if (track_info->amr_modes & 0x0002)
        mem_append("1", amr_modes);
      if (track_info->amr_modes & 0x0004)
        mem_append("2", amr_modes);
      if (track_info->amr_modes & 0x0008)
        mem_append("3", amr_modes);
      if (track_info->amr_modes & 0x0010)
        mem_append("4", amr_modes);
      if (track_info->amr_modes & 0x0020)
        mem_append("5", amr_modes);
      if (track_info->amr_modes & 0x0040)
        mem_append("6", amr_modes);
      if (track_info->amr_modes & 0x0080)
        mem_append("7", amr_modes);
      if (track_info->amr_modes & 0x0100)
        mem_append("8", amr_modes);
      if (strlen(amr_modes) == 0)
        memcpy(amr_modes, "none", 4);
    } else if (track_info->track_codec == 0x73766D72) {
      if (track_info->amr_modes & 0x0001)
        mem_append("VMR-WB Mode 0, ", amr_modes);
      if (track_info->amr_modes & 0x0002)
        mem_append("VMR-WB Mode 1, ", amr_modes);
      if (track_info->amr_modes & 0x0004)
        mem_append("VMR-WB Mode 2, ", amr_modes);
      if (track_info->amr_modes & 0x0008)
        mem_append("VMR-WB Mode 3 (AMR-WB interoperable mode), ", amr_modes);
      if (track_info->amr_modes & 0x0010)
        mem_append("VMR-WB Mode 4, ", amr_modes);
      if (track_info->amr_modes & 0x0020)
        mem_append("VMR-WB Mode 2 with maximum half-rate, ", amr_modes);
      if (track_info->amr_modes & 0x0040)
        mem_append("VMR-WB Mode 4 with maximum half-rate, ", amr_modes);
      uint16_t amr_modes_len = strlen(amr_modes);
      if (amr_modes_len > 0)
        memset(amr_modes + (amr_modes_len - 1), 0, 2);
    }

    if (track_info->track_codec == 0x73616D72) {
      fprintf(stdout,
              "  AMR Narrow-Band. Modes: %s. Encoder vendor code: %s\n",
              amr_modes,
              track_info->encoder_name);
    } else if (track_info->track_codec == 0x73617762) {
      fprintf(stdout,
              "  AMR Wide-Band. Modes: %s. Encoder vendor code: %s\n",
              amr_modes,
              track_info->encoder_name);
    } else if (track_info->track_codec == 0x73617770) {
      fprintf(stdout,
              "  AMR Wide-Band WB+. Encoder vendor code: %s\n",
              track_info->encoder_name);
    } else if (track_info->track_codec == 0x73766D72) {
      fprintf(stdout,
              "  AMR VBR Wide-Band. Encoder vendor code: %s\n",
              track_info->encoder_name);
    }
  } else if (track_type == EVRC_TRACK) {
    fprintf(stdout,
            "  EVRC (Enhanced Variable Rate Coder). Encoder vendor code: %s\n",
            track_info->encoder_name);

  } else if (track_type == QCELP_TRACK) {
    fprintf(stdout,
            "  QCELP (Qualcomm Code Excited Linear Prediction). Encoder vendor "
            "code: %s\n",
            track_info->encoder_name);

  } else if (track_type == S263_TRACK) {
    if (track_info->profile == 0) {
      fprintf(stdout,
              "  H.263 Baseline Profile, Level %u. Encoder vendor code: %s",
              track_info->level,
              track_info->encoder_name);
    } else {
      fprintf(stdout,
              "  H.263 Profile: %u, Level %u. Encoder vendor code: %s",
              track_info->profile,
              track_info->level,
              track_info->encoder_name);
    }
  }
  if (track_type == AUDIO_TRACK) {
    if (track_info->section5_length == 0) {
      fprintf(stdout, "    channels: (%u)\n", track_info->channels);
    } else {
      fprintf(stdout, "    channels: [%u]\n", track_info->channels);
    }
  }
}
