pclxl_beginpage(gx_device_vector * vdev)
{
    gx_device_pclxl *const xdev = (gx_device_pclxl *)vdev;


    stream *s = vdev->strm;
    byte media_source = eAutoSelect;

    xdev->page ++;


    px_write_page_header(s, (const gx_device *)vdev);

    if (xdev->ManualFeed_set && xdev->ManualFeed)
        media_source = 2;
    else if (xdev->MediaPosition_set && xdev->MediaPosition >= 0 )
        media_source = xdev->MediaPosition;

    px_write_select_media(s, (const gx_device *)vdev, &xdev->media_size,
                          &media_source,
                          xdev->page, xdev->Duplex, xdev->Tumble,
                          xdev->MediaType_set, xdev->MediaType);

    spputc(s, pxtBeginPage);
    return 0;
}
