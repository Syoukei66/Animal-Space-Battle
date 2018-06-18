#pragma once

#include <string>

class ResourceLoader
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  ResourceLoader(const std::string& category)
    : category_(category)
  {}
  virtual ~ResourceLoader() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Load() = 0;
  virtual void Unload() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
  inline const std::string& GetCategory() const
  {
    return this->category_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const std::string category_;

};