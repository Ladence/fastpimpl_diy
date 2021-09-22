#include <iostream>
#include <thread>

#include "backup_policy.h"

using namespace policies;

class BackupPolicyImpl
{
public:
    BackupPolicyImpl() = default;
    BackupPolicyImpl(const BackupPolicyImpl&) = default;
    BackupPolicyImpl(BackupPolicyImpl&&) noexcept = default;
    BackupPolicyImpl& operator=(const BackupPolicyImpl&) = default;
    BackupPolicyImpl& operator=(BackupPolicyImpl&&) noexcept = default;
    ~BackupPolicyImpl() = default;

    void doBackup() {
        for (int i = 0; i <= 100; i += 20) {
            std::cout << "Backup progress: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds{2});
        }
        std::cout << "Backup is done!" << std::endl;
    }
};

void BackupPolicy::doBackup() {
    m_pimpl->doBackup();
}

BackupPolicy::BackupPolicy() : m_pimpl{} {}

BackupPolicy::BackupPolicy(const BackupPolicy&) = default;
BackupPolicy::BackupPolicy(BackupPolicy&&) noexcept = default;
BackupPolicy& BackupPolicy::operator=(const BackupPolicy&) = default;
BackupPolicy& BackupPolicy::operator=(BackupPolicy&&) noexcept = default;
BackupPolicy::~BackupPolicy() = default;
