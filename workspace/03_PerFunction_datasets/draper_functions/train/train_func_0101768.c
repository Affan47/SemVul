GetAngle(const WorldObject* obj) const
{
    if (!obj)
        { return 0.0f; }


    if (obj == this)
    {
        sLog.outError("INVALID CALL for GetAngle for %s", obj->GetGuidStr().c_str());
        return 0.0f;
    }
    return GetAngle(obj->GetPositionX(), obj->GetPositionY());
}
