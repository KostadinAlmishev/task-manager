//
// Created by Konstantin Pronin on 06.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_CONFIG_CONFIGVALIDATOR_H_
#define TASKMANAGER_INCLUDE_DATABASE_CONFIG_CONFIGVALIDATOR_H_

#include <memory>

class DbConfig;

class ConfigValidator {
 protected:
  std::shared_ptr<ConfigValidator> _next;
 public:
  explicit ConfigValidator(std::shared_ptr<ConfigValidator>);
  virtual void validate(const std::string &, const std::string &, DbConfig &) const = 0;
  virtual ~ConfigValidator() = default;
};

class HostValidator : public ConfigValidator {
 public:
  explicit HostValidator(std::shared_ptr<ConfigValidator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~HostValidator() override = default;
};

class PortValidator : public ConfigValidator {
 public:
  explicit PortValidator(std::shared_ptr<ConfigValidator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~PortValidator() override = default;
};

class DbNameValidator : public ConfigValidator {
 public:
  explicit DbNameValidator(std::shared_ptr<ConfigValidator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~DbNameValidator() override = default;
};

class UserValidator : public ConfigValidator {
 public:
  explicit UserValidator(std::shared_ptr<ConfigValidator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~UserValidator() override = default;
};

class PasswordValidator : public ConfigValidator {
 public:
  explicit PasswordValidator(std::shared_ptr<ConfigValidator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~PasswordValidator() override = default;
};

class PoolSizeValidator : public ConfigValidator {
 public:
  explicit PoolSizeValidator(std::shared_ptr<ConfigValidator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~PoolSizeValidator() override = default;
};
#endif //TASKMANAGER_INCLUDE_DATABASE_CONFIG_CONFIGVALIDATOR_H_
