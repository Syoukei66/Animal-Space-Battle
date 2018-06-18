#pragma once

class DeveloperSettings
{
public:
  static DeveloperSettings* GetInstance()
  {
    static DeveloperSettings self;
    return &self;
  }

private:
  DeveloperSettings()
  {}

public:
  ~DeveloperSettings()
  {}

public:
  void Load();

public:
  bool IsDebugMode() const
  {
    return this->debug_mode_;
  }
  bool IsModelLoad() const
  {
    return this->load_model_;
  }
  const TSize& GetWindowSize() const
  {
    return this->window_size_;
  }

private:
  bool debug_mode_;
  bool load_model_;
  TSize window_size_;
};