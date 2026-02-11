newGlobalRef(jobject obj, int id)
{
    if (obj)
    {
        if (id)
        {
            lock locked;

            for (std::multimap<int, countedRef>::iterator iter = refs.find(id);
                 iter != refs.end();
                 iter++) {
                if (iter->first != id)
                    break;
                if (isSame(obj, iter->second.global))
                {


                    if (obj != iter->second.global)
                        get_vm_env()->DeleteLocalRef(obj);

                    iter->second.count += 1;
                    return iter->second.global;
                }
            }

            JNIEnv *vm_env = get_vm_env();
            countedRef ref;

            ref.global = vm_env->NewGlobalRef(obj);
            ref.count = 1;
            refs.insert(std::pair<const int, countedRef>(id, ref));
            vm_env->DeleteLocalRef(obj);

            return ref.global;
        }
        else
            return (jobject) get_vm_env()->NewWeakGlobalRef(obj);
    }

    return NULL;
}
