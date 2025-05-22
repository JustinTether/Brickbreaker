#pragma once
#include "BaseUpgrade.h"
#include <functional>
#include <map>
#include <memory>
#include <vector>

class UpgradeFactory
{
public:
  // Typedef for the function signature required to create a BaseUpgrade derived
  // object
  using CreateUpgradeFunction = std::function<std::shared_ptr<BaseUpgrade>()>;

  void RegisterUpgrade(const std::string& UpgradeType,
                       CreateUpgradeFunction CreateFunction)
  {
    CreationFunctions[UpgradeType] = CreateFunction;
    RegisteredUpgrades.push_back(UpgradeType);
  }

  std::shared_ptr<BaseUpgrade>
  CreateUpgrade(const std::string& UpgradeType) const
  {
    auto it = CreationFunctions.find(UpgradeType);

    if (it != CreationFunctions.end())
    {
      return it->second();
    }
    return nullptr;
  }

  const std::vector<std::string>& GetRegisteredUpgrades() const
  {
    return RegisteredUpgrades;
  }

private:
  std::map<std::string, CreateUpgradeFunction> CreationFunctions;
  std::vector<std::string> RegisteredUpgrades;
};
