_format(int device_num, char fs_name, int blocksize){

    int i;
    int error = 0;

    if (blocksize != 4 && blocksize != 8 && blocksize != 16){
        return ERROR_INVALID_BLOCK_SIZE;
    }

    if(device_num < 0 || device_num >= MAX_DEVICE){
        return ERROR_INVALID_DEVICE_NUM;
    }
    device *format_me = &device_array[device_num];

    if(format_me->bits & DEVICE_MOUNTED_BITMASK){
        return ERROR_DEVICE_MOUNTED;
    }
    if(!(format_me->bits & DEVICE_INIT_BITMASK)){
        return ERROR_DEVICE_NOT_KNOWN;
    }

    if (fs_name < 'A' || fs_name > 'Z') {
        return ERROR_BAD_FS_NAME;
    }

    format_me->fs_name = fs_name;
    format_me->numblock = MEM_SIZE/(blocksize<<10);
    if (format_me->root != null && !(format_me->bits & DEVICE_INIT_BITMASK)) {

        error = delete_internal(device_num, format_me->root);
    }

    if (error < 0) {

    }


    for(i = 0; i < MEM_SIZE / (blocksize << 10); i++){
        format_me->bitmap[i] = 0;
    }
    format_me->bits = format_me->bits | DEVICE_FORMAT_BITMASK;

    format_me->root = malloc_file();
    filename_copy(format_me->root->filename,"root");
    format_me->root->bits = 1;
    format_me->root->dirHead = malloc_dir_queue();

    dir_init_queue(format_me->root->dirHead);


    format_me->root->parent_dir = null;
    format_me->root->block_queue = null;
    format_me->root->next = null;
    format_me->root->prev = null;
    format_me->root->device_num = device_num;
    format_me->root->error = 0;

    return format_me->numblock;
}
