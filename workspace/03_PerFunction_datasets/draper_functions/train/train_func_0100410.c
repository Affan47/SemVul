H5T_upgrade_version_cb(H5T_t *dt, void *op_value)
{
    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(dt);
    HDassert(op_value);


    switch(dt->shared->type) {
        case H5T_COMPOUND:
        case H5T_ARRAY:
        case H5T_ENUM:

            if(*(unsigned *)op_value > dt->shared->version)
                dt->shared->version = *(unsigned *)op_value;
            break;

        case H5T_VLEN:
            if(dt->shared->parent->shared->version > dt->shared->version)
                dt->shared->version = dt->shared->parent->shared->version;
            break;

        case H5T_NO_CLASS:
        case H5T_INTEGER:
        case H5T_FLOAT:
        case H5T_TIME:
        case H5T_STRING:
        case H5T_BITFIELD:
        case H5T_OPAQUE:
        case H5T_REFERENCE:
        case H5T_NCLASSES:
        default:
            break;
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
