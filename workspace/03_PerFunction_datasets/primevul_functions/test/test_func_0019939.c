static bool vnc_should_update(VncState *vs)
{
    switch (vs->update) {
    case VNC_STATE_UPDATE_NONE:
        break;
    case VNC_STATE_UPDATE_INCREMENTAL:


        if (vs->output.offset < vs->throttle_output_offset &&
            vs->job_update == VNC_STATE_UPDATE_NONE) {
            return true;
        }
        trace_vnc_client_throttle_incremental(
            vs, vs->ioc, vs->job_update, vs->output.offset);
        break;
    case VNC_STATE_UPDATE_FORCE:


        if (vs->force_update_offset == 0 &&
            vs->job_update == VNC_STATE_UPDATE_NONE) {
            return true;
        }
        trace_vnc_client_throttle_forced(
            vs, vs->ioc, vs->job_update, vs->force_update_offset);
        break;
    }
    return false;
}
