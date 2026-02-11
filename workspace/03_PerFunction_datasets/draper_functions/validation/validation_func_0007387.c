tile_fill_init(tile_fill_state_t * ptfs, const gx_device_color * pdevc,
               gx_device * dev, bool set_mask_phase)
{
    gx_color_tile *m_tile = pdevc->mask.m_tile;
    int px, py;
    bool is_planar;

    ptfs->pdevc = pdevc;
    is_planar = dev_proc(dev, dev_spec_op)(dev, gxdso_is_native_planar, NULL, 0) > 0;
    if (is_planar) {
        ptfs->num_planes = dev->color_info.num_components;
    } else {
        ptfs->num_planes = -1;
    }
    if (m_tile == 0) {
        ptfs->cdev = NULL;
        ptfs->pcdev = dev;
        ptfs->phase = pdevc->phase;
        return 0;
    }
    if ((ptfs->cdev = (gx_device_tile_clip *)gs_alloc_struct(dev->memory,
                                                 gx_device_tile_clip,
                                                 &st_device_tile_clip,
                                                 "tile_fill_init(cdev)")) == NULL) {
        return_error(gs_error_VMerror);
    }
    ptfs->cdev->finalize = NULL;
    ptfs->pcdev = (gx_device *)ptfs->cdev;
    ptfs->tmask = &m_tile->tmask;
    ptfs->phase.x = pdevc->mask.m_phase.x;
    ptfs->phase.y = pdevc->mask.m_phase.y;


    if (set_mask_phase && m_tile->is_simple) {
        px = imod(-(int)fastfloor(m_tile->step_matrix.tx - ptfs->phase.x + 0.5),
                  m_tile->tmask.rep_width);
        py = imod(-(int)fastfloor(m_tile->step_matrix.ty - ptfs->phase.y + 0.5),
                  m_tile->tmask.rep_height);
    } else
        px = py = 0;
    return tile_clip_initialize(ptfs->cdev, ptfs->tmask, dev, px, py);
}
