void SshIo::SshImpl::writeRemote(const byte* data, size_t size, long from, long to)
    {
        if (protocol_ == pSftp) throw Error(1, "not support SFTP write access.");


        assert(isMalloced_);

        std::string tempFile = hostInfo_.Path + ".exiv2tmp";
        std::string response;
        std::stringstream ss;

        ss  << "head -c " << from
            << " "   << hostInfo_.Path
            << " > " << tempFile;
        std::string cmd = ss.str();
        if (ssh_->runCommand(cmd, &response) != 0) {
            throw Error(1, "SSH: Unable to cope the head of file to temp");
        }


        if (ssh_->scp(hostInfo_.Path + ".exiv2datatemp", data, size) != 0) {
            throw Error(1, "SSH: Unable to copy file");
        }


        cmd = "cat " + hostInfo_.Path + ".exiv2datatemp >> " + tempFile;
        if (ssh_->runCommand(cmd, &response) != 0) {
            throw Error(1, "SSH: Unable to copy the rest");
        }


        ss.str("");
        ss  << "tail -c+" << (to + 1)
            << " "   << hostInfo_.Path
            << " >> "   << tempFile;
        cmd = ss.str();
        if (ssh_->runCommand(cmd, &response) != 0) {
            throw Error(1, "SSH: Unable to copy the rest");
        }


        cmd = "mv " + tempFile + " " + hostInfo_.Path;
        if (ssh_->runCommand(cmd, &response) != 0) {
            throw Error(1, "SSH: Unable to copy the rest");
        }


        cmd = "rm " + hostInfo_.Path + ".exiv2datatemp";
        if (ssh_->runCommand(cmd, &response) != 0) {
            throw Error(1, "SSH: Unable to copy the rest");
        }
    }
