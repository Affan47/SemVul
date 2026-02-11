setGyroLpf(unsigned char lpf)
{
    switch (lpf) {
    case MPU9250_GYRO_LPF_8800:
    case MPU9250_GYRO_LPF_3600:
    case MPU9250_GYRO_LPF_250:
    case MPU9250_GYRO_LPF_184:
    case MPU9250_GYRO_LPF_92:
    case MPU9250_GYRO_LPF_41:
    case MPU9250_GYRO_LPF_20:
    case MPU9250_GYRO_LPF_10:
    case MPU9250_GYRO_LPF_5:
        m_gyroLpf = lpf;
        return true;

    default:
        HAL_ERROR1("Illegal MPU9250 gyro lpf %d\n", lpf);
        return false;
    }
}
