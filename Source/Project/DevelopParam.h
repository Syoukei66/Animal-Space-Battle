#pragma once

#include <HalEngine.h>

class DevelopParam
{
public:
  virtual void LoadFromJson(JsonNode* node) = 0;
  virtual void ToJson(JsonNode* dest) = 0;

  virtual bool EditWithImgui() = 0;
  virtual void ResetFlags() = 0;

};
