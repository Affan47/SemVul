stsd_read_subtitle_qt(bgav_input_context_t * input,
                                 qt_sample_description_t * ret)
  {
  ret->type = BGAV_STREAM_SUBTITLE_TEXT;
  if(!bgav_input_read_fourcc(input, &ret->fourcc) ||
     (bgav_input_read_data(input, ret->reserved, 6) < 6) ||
     !bgav_input_read_16_be(input, &ret->data_reference_index) ||
     !bgav_input_read_32_be(input, &ret->format.subtitle_qt.displayFlags) ||
     !bgav_input_read_32_be(input, &ret->format.subtitle_qt.textJustification) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.bgColor[0]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.bgColor[1]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.bgColor[2]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.defaultTextBox[0]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.defaultTextBox[1]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.defaultTextBox[2]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.defaultTextBox[3]) ||
     !bgav_input_read_32_be(input, &ret->format.subtitle_qt.scrpStartChar) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpHeight) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpAscent) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpFont) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpFace) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpSize) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpColor[0]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpColor[1]) ||
     !bgav_input_read_16_be(input, &ret->format.subtitle_qt.scrpColor[2]) ||
     !bgav_input_read_string_pascal(input, ret->format.subtitle_qt.font_name))
    return 0;
  return 1;
  }
