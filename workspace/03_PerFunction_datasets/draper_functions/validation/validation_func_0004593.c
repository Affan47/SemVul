mei_me_cl_rm_by_uuid_id(struct mei_device *dev, const uuid_le *uuid, u8 id)
{
	struct mei_me_client *me_cl;

	dev_dbg(dev->dev, "remove %pUl %d\n", uuid, id);

	down_write(&dev->me_clients_rwsem);
	me_cl = __mei_me_cl_by_uuid_id(dev, uuid, id);
	__mei_me_cl_del(dev, me_cl);
	up_write(&dev->me_clients_rwsem);
}
