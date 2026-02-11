clj_pr_put_params(
    gx_device *             pdev,
    gs_param_list *         plist
)
{
    float		    mediasize[2];
    int                     code = 0;
    bool                    rotate = false;
    int                     have_pagesize = clj_media_size(mediasize, plist);

    if (have_pagesize < 0)
        return have_pagesize;
    if (have_pagesize) {
        if (get_paper_size(mediasize, &rotate) == 0)
            return_error(gs_error_rangecheck);
        if (rotate) {


            gs_param_float_array	pf_array;
            gs_c_param_list		alist;
            float			ftmp = mediasize[0];

            mediasize[0] = mediasize[1];
            mediasize[1] = ftmp;
            pf_array.data = mediasize;
            pf_array.size = 2;
            pf_array.persistent = false;

            gs_c_param_list_write(&alist, pdev->memory);
            code = param_write_float_array((gs_param_list *)&alist, ".MediaSize", &pf_array);
            gs_c_param_list_read(&alist);


            gs_c_param_list_set_target(&alist, plist);
            if ((code = gdev_prn_put_params(pdev, (gs_param_list *)&alist)) >= 0)
                pclj->rotated = true;
            gs_c_param_list_release(&alist);
        } else {
            if ((code = gdev_prn_put_params(pdev, plist)) >= 0)
                pclj->rotated = false;
        }
    } else
        code = gdev_prn_put_params(pdev, plist);

    return code;
}
