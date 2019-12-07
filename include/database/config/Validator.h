//
// Created by Konstantin Pronin on 06.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_CONFIG_VALIDATOR_H_
#define TASKMANAGER_INCLUDE_DATABASE_CONFIG_VALIDATOR_H_

#include <memory>

class DbConfig;

class Validator {
 protected:
  std::shared_ptr<Validator> _next;
 public:
  explicit Validator(std::shared_ptr<Validator>);
  virtual void validate(const std::string &, const std::string &, DbConfig &) const = 0;
  virtual ~Validator() = default;
};

class HostValidator : public Validator {
 public:
  explicit HostValidator(std::shared_ptr<Validator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~HostValidator() override = default;
};

class PortValidator : public Validator {
 public:
  explicit PortValidator(std::shared_ptr<Validator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~PortValidator() override = default;
};

class DbNameValidator : public Validator {
 public:
  explicit DbNameValidator(std::shared_ptr<Validator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~DbNameValidator() override = default;
};

class UserValidator : public Validator {
 public:
  explicit UserValidator(std::shared_ptr<Validator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~UserValidator() override = default;
};

class PasswordValidator : public Validator {
 public:
  explicit PasswordValidator(std::shared_ptr<Validator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~PasswordValidator() override = default;
};

class PoolSizeValidator : public Validator {
 public:
  explicit PoolSizeValidator(std::shared_ptr<Validator>);
  void validate(const std::string &, const std::string &, DbConfig &) const override;
  ~PoolSizeValidator() override = default;
};
#endif //TASKMANAGER_INCLUDE_DATABASE_CONFIG_VALIDATOR_H_
