reset_object_address(
    void const * const new_address,
    void const * const old_address
){
    if(m_moveable_objects.is_pointer)
        return;


    object_id_type i;
    for(i = m_moveable_objects.recent; i < m_moveable_objects.end; ++i){
        if(old_address == object_id_vector[i].address)
            break;
    }
    for(; i < m_moveable_objects.end; ++i){
        void const * const this_address = object_id_vector[i].address;


        if(this_address > old_address){
            std::size_t member_displacement
                = reinterpret_cast<std::size_t>(this_address)
                - reinterpret_cast<std::size_t>(old_address);
            object_id_vector[i].address = reinterpret_cast<void *>(
                reinterpret_cast<std::size_t>(new_address) + member_displacement
            );
        }
        else{
            std::size_t member_displacement
                = reinterpret_cast<std::size_t>(old_address)
                - reinterpret_cast<std::size_t>(this_address);
            object_id_vector[i].address = reinterpret_cast<void *>(
                reinterpret_cast<std::size_t>(new_address) - member_displacement
            );
       }
    }
}
