#ifndef SECRET_VAULT_HPP
#define SECRET_VAULT_HPP

#include "singleton.hpp"
#include "file_parser.hpp"

#include <unordered_map>

template <typename Secret>
class VaultOfSecrets : public Singleton<VaultOfSecrets<Secret>>
{
public:
    ~VaultOfSecrets() = default;
    VaultOfSecrets(VaultOfSecrets const& other) = delete;
    VaultOfSecrets& operator=(VaultOfSecrets const& other) = delete;

    std::string add(Secret const& a_secret);
    Secret const& fetch(std::string const& a_key);

    void save() const;
    void load();

    friend class Singleton<VaultOfSecrets<Secret>>;

private:
    VaultOfSecrets();
    std::string generate_key();

private:
    std::unordered_map<std::string, Secret> m_secrets;
    FileParser<std::string, Secret>* m_file_parser;
};

#include "inl/vault_secrets.hxx"

#endif // SECRET_VAULT_HPP