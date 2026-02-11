duplicateInterfaces(FWObject *target, const FWObject *source,
                                   map<int,int> &id_mapping, bool preserve_id)
{
    for (FWObjectTypedChildIterator m = source->findByType(Interface::TYPENAME);
         m!=m.end(); ++m )
    {
        FWObject *src_interface = *m;
        FWObject *dst_interface_copy =
            target->addCopyOf(src_interface, preserve_id);

        id_mapping[src_interface->getId()] = dst_interface_copy->getId();

        Interface::cast(dst_interface_copy)->duplicateWithIdMapping(
            src_interface, id_mapping, preserve_id);

#if 0
        if (Firewall::cast(target))
        {


            for (FWObjectTypedChildIterator k = src_interface->findByType(FailoverClusterGroup::TYPENAME);
                 k!=k.end(); ++k )
            {
                FWObject *src_subinterface  = *k;
                FWObject *dst_subinterface_copy =
                    dst_interface_copy->addCopyOf(src_subinterface, preserve_id);

                if (src_subinterface!=NULL && dst_subinterface_copy!=NULL)
                    id_mapping[src_subinterface->getId()] = dst_subinterface_copy->getId();
            }

            duplicateInterfaces(dst_interface_copy, src_interface,
                                id_mapping, preserve_id);
        }
#endif

    }
}
