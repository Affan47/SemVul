Resize() {
    if (!flag.hidden) {
        while (update_info.resize) {
            resize_requested_by_parent();
            if (parent) break;
        }
    }

    return ED4_R_OK;
}
