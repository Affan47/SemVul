gst_midi_parse_class_init (GstMidiParseClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->finalize = gst_midi_parse_finalize;
  gobject_class->set_property = gst_midi_parse_set_property;
  gobject_class->get_property = gst_midi_parse_get_property;

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_factory));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_factory));
  gst_element_class_set_static_metadata (gstelement_class, "MidiParse",
      "Codec/Demuxer/Audio",
      "Midi Parser Element", "Wim Taymans <wim.taymans@gmail.com>");

  GST_DEBUG_CATEGORY_INIT (gst_midi_parse_debug, "midiparse",
      0, "MIDI parser plugin");

  gstelement_class->change_state = gst_midi_parse_change_state;
}
