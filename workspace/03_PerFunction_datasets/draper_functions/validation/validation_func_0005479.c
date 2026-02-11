DequeueEvent()
{
    jack_midi_event_t *e = 0;
    if (index < event_count) {
        JackMidiEvent *event = &(buffer->events[index]);
        midi_event.buffer = event->GetData(buffer);
        midi_event.size = event->size;
        midi_event.time = last_frame_time + event->time;
        e = &midi_event;
        index++;
    }
    return e;
}
