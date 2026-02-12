njs_vm_retval_string(njs_vm_t *vm, njs_str_t *dst)
{
    if (vm->top_frame == NULL) {


        njs_vm_init(vm);
    }

    return njs_vm_value_string(vm, dst, &vm->retval);
}
