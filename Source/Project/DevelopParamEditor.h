#pragma once

#include <HalEngine.h>

#include "DevelopParam.h"

class DevelopParamEditor
{
public:
  DevelopParamEditor(DevelopParam* param, const char* directory_path, const char* file_path);
  void Update();

private:
  DevelopParam* param_;
  char directory_path_[256];
  char file_path_[256];

};