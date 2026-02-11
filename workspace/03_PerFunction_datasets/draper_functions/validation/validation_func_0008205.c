attachCameraInterface(as_object& o)
{

    const int flags = as_object::DefaultFlags | PropFlags::onlySWF6Up;

    VM& vm = getVM(o);
    o.init_member("setMode", vm.getNative(2102, 0), flags);
    o.init_member("setQuality", vm.getNative(2102, 1), flags);
    o.init_member("setKeyFrameInterval", vm.getNative(2102, 2), flags);
    o.init_member("setMotionLevel", vm.getNative(2102, 3), flags);
    o.init_member("setLoopback", vm.getNative(2102, 4), flags);
    o.init_member("setCursor", vm.getNative(2102, 5), flags);

}
