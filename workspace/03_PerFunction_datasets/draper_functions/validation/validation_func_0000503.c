gst_audio_delay_tempo_change_tempo(GstBtTempo *tempo, glong beats_per_minute, glong ticks_per_beat, glong subticks_per_tick) {
  GstBtAudioDelay *self=GSTBT_AUDIO_DELAY(tempo);
  gboolean changed=FALSE;

  if(beats_per_minute>=0) {
    if(self->beats_per_minute!=beats_per_minute) {
      self->beats_per_minute=(gulong)beats_per_minute;
      g_object_notify(G_OBJECT(self),"beats-per-minute");
      changed=TRUE;
    }
  }
  if(ticks_per_beat>=0) {
    if(self->ticks_per_beat!=ticks_per_beat) {
      self->ticks_per_beat=(gulong)ticks_per_beat;
      g_object_notify(G_OBJECT(self),"ticks-per-beat");
      changed=TRUE;
    }
  }
  if(subticks_per_tick>=0) {
    if(self->subticks_per_tick!=subticks_per_tick) {
      self->subticks_per_tick=(gulong)subticks_per_tick;
      g_object_notify(G_OBJECT(self),"subticks-per-tick");
      changed=TRUE;
    }
  }
  if(changed) {
    GST_DEBUG("changing tempo to %ld BPM  %ld TPB  %ld STPT",self->beats_per_minute,self->ticks_per_beat,self->subticks_per_tick);
    gst_audio_delay_calculate_tick_time(self);
  }
}
