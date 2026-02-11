bbox_fill_mask(gx_device * dev,
               const byte * data, int dx, int raster, gx_bitmap_id id,
               int x, int y, int w, int h,
               const gx_drawing_color * pdcolor, int depth,
               gs_logical_operation_t lop, const gx_clip_path * pcpath)
{
    gx_device_bbox *const bdev = (gx_device_bbox *) dev;
    gx_device *tdev = bdev->target;

    int code =
        (tdev == 0 ? 0 :
         dev_proc(tdev, fill_mask)
         (tdev, data, dx, raster, id, x, y, w, h,
          pdcolor, depth, lop, pcpath));

    if (pcpath != NULL &&
        !gx_cpath_includes_rectangle(pcpath, int2fixed(x), int2fixed(y),
                                     int2fixed(x + w),
                                     int2fixed(y + h))
        ) {


        bdev->target = NULL;
        gx_default_fill_mask(dev, data, dx, raster, id, x, y, w, h,
                             pdcolor, depth, lop, pcpath);
        bdev->target = tdev;
    } else {

        BBOX_ADD_INT_RECT(bdev, x, y, x + w, y + h);
    }
    return code;
}
