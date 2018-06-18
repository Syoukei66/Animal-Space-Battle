#pragma once

#include <HalEngine.h>
#include "DevelopParam.h"

class DesignData : public DevelopParam
{
public:
  enum Anchor
  {
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    LEFT,
    CENTER,
    RIGHT,
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT,

    OUTER_TOP_LEFT,
    OUTER_TOP,
    OUTER_TOP_RIGHT,
    OUTER_LEFT,
    OUTER_CENTER,
    OUTER_RIGHT = OUTER_CENTER,
    OUTER_BOTTOM_LEFT,
    OUTER_BOTTOM,
    OUTER_BOTTOM_RIGHT,

    ANCHOR_DATANUM,
  };

  static const char* GetAnchorText();

  enum SizeType
  {
    SIZE,
    SCALE,
  };

public:
  DesignData(const char* name);

public:
  virtual void LoadFromJson(JsonNode* node) override;
  virtual void ToJson(JsonNode* dest) override;
  virtual bool EditWithImgui() override;
  virtual void ResetFlags() override;

public:
  void ConvertSize(T_FLOAT width, T_FLOAT height, TAreaf* dest) const;

public:
  inline void SetParent(DesignData* parent)
  {
    this->parent_ = parent;
  }
  inline DesignData* GetParent() const
  {
    return this->parent_;
  }
  inline bool IsDirty() const
  {
    return this->is_dirty_;
  }
  inline T_INT32 GetAnchor() const
  {
    return this->anchor_;
  }
  inline const T_FLOAT GetX() const
  {
    return this->pos_[0];
  }
  inline const T_FLOAT GetY() const
  {
    return this->pos_[1];
  }
  inline void SetSizeType(SizeType type)
  {
    this->size_type_ = type;
  }
  inline T_INT32 GetSizeType() const
  {
    return this->size_type_;
  }
  inline T_FLOAT GetWidth() const
  {
    return this->size_[0];
  }
  inline T_FLOAT GetHeight() const
  {
    return this->size_[1];
  }
  inline T_FLOAT GetScale() const
  {
    return this->size_[0];
  }

private:
  DesignData* parent_;

  std::string name_;

  std::string id_anchor_;
  std::string id_pos_;
  std::string id_size_;
  std::string id_scale_;

  T_INT32 anchor_;
  T_FLOAT pos_[2];
  T_INT32 size_type_;
  T_FLOAT size_[2];
  bool is_dirty_;

  TAreaf cache_;

};
