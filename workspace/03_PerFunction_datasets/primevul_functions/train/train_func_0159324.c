static void qxl_vm_change_state_handler(void *opaque, int running,
                                        RunState state)
{
    PCIQXLDevice *qxl = opaque;

    if (running) {


         qxl_update_irq(qxl);
    } else {

        qxl_dirty_surfaces(qxl);
    }
}
