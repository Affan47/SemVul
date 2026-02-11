abuf_flush(gx_device_memory * adev)
{
    int y, code = 0;
    int block_height = 1 << adev->log2_scale.y;

    for (y = 0; y < adev->mapped_height; y += block_height)
        if ((code = abuf_flush_block(adev, adev->mapped_y + y)) < 0)
            return code;
    adev->mapped_height = adev->mapped_start = 0;
    return 0;
}
