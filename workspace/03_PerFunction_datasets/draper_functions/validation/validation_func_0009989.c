save_writeback_all_axes()
{
    AXIS_INDEX axis;

    for (axis = 0; axis < AXIS_ARRAY_SIZE; axis++)
	if (axis_array[axis].range_flags & RANGE_WRITEBACK) {
	    set_writeback_min(axis);
	    set_writeback_max(axis);
	}
}
