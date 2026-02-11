plane_fill_mask(gx_device *dev,
    const byte *data, int data_x, int raster, gx_bitmap_id id,
    int x, int y, int w, int h,
    const gx_drawing_color *pdcolor, int depth,
    gs_logical_operation_t lop, const gx_clip_path *pcpath)
{
    gx_device_plane_extract * const edev = (gx_device_plane_extract *)dev;
    gx_device * const plane_dev = edev->plane_dev;
    gx_device_color dcolor;

    switch (reduce_drawing_color(&dcolor, edev, pdcolor, &lop)) {
    case REDUCE_SKIP:
        return 0;
    case REDUCE_DRAW:
        return dev_proc(plane_dev, fill_mask)
            (plane_dev, data, data_x, raster, gx_no_bitmap_id, x, y, w, h,
             &dcolor, depth, lop, pcpath);
    default :
        return gx_default_fill_mask(dev, data, data_x, raster, gx_no_bitmap_id,
                                    x, y, w, h, &dcolor, depth, lop, pcpath);
    }
}
