test_heap_insert_many_core(H5HP_type_t heap_type, test_obj *arr, size_t nelem, int top_val)
{
    H5HP_t *heap;
    ssize_t num;
    int val;
    size_t u;
    herr_t ret;


    heap=H5HP_create(heap_type);
    CHECK(heap, NULL, "H5HP_create");


    num=H5HP_count(heap);
    VERIFY(num, 0, "H5HP_count");


    for(u=0; u<nelem; u++) {
        ret=H5HP_insert(heap,arr[u].val,&arr[u]);
        CHECK(ret, FAIL, "H5HP_insert");
    }


    num=H5HP_count(heap);
    CHECK(num, FAIL, "H5HP_count");
    VERIFY((size_t)num, nelem, "H5HP_count");


    ret=H5HP_top(heap, &val);
    CHECK(ret, FAIL, "H5HP_top");
    VERIFY(val, top_val, "H5HP_top");


    ret=H5HP_close(heap);
    CHECK(ret, FAIL, "H5HP_close");
}
