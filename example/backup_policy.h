#pragma once

#include "fast_pimpl.h"

class BackupPolicyImpl;

namespace policies
{
class BackupPolicy
{
public:
    BackupPolicy();
    BackupPolicy(const BackupPolicy&);
    BackupPolicy(BackupPolicy&&) noexcept;
    BackupPolicy& operator=(const BackupPolicy&);
    BackupPolicy& operator=(BackupPolicy&&) noexcept;
    ~BackupPolicy();

    void doBackup();

private:
    static constexpr std::size_t DATA_IMPL_SIZE = 1;
    static constexpr std::size_t DATA_IMPL_ALIGNMENT = 1;

    fast_pimpl::pimpl<BackupPolicyImpl, DATA_IMPL_SIZE, DATA_IMPL_ALIGNMENT> m_pimpl;
};
}