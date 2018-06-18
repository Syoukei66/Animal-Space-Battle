#include "DesignData.h"
#include <stdio.h>

static const char* ID_ANCHOR = "Anchor";
static const char* ID_X = "X";
static const char* ID_Y = "Y";
static const char* ID_WIDTH = "Width";
static const char* ID_HEIGHT = "Height";
static const char* ID_SCALE = "Scale";

static const char ANCHOR_TEXT[DesignData::ANCHOR_DATANUM][256] =
{
  "左上",
  "上",
  "右上",
  "左",
  "中央",
  "右",
  "左下",
  "下",
  "右下",

  "左上(外側)",
  "上(外側)",
  "右上(外側)",
  "左(外側)",
  "右(外側)",
  "左下(外側)",
  "下(外側)",
  "右下(外側)",
};

const char* DesignData::GetAnchorText()
{
  return u8"左上\0上\0右上\0左\0中央\0右\0左下\0下\0右下\0左上(外側)\0上(外側)\0右上(外側)\0左(外側)\0右(外側)\0左下(外側)\0下(外側)\0右下(外側)";
  static bool initialized = false;
  static char text[256] = {};
  if (!initialized)
  {
    std::string s = std::string();
    for (T_UINT8 i = 0; i < ANCHOR_DATANUM; ++i)
    {
      s.append(ANCHOR_TEXT[i]);
      s.append("\0");
    }
    s.append("\0");
    initialized = true;
  }
  return text;
}

DesignData::DesignData(const char* name)
  : parent_(nullptr)
  , name_(name)
  , anchor_(Anchor::CENTER)
  , pos_()
  , size_()
{
  this->id_anchor_ = name;
  this->id_anchor_.append(ID_ANCHOR);
  this->id_pos_ = name;
  this->id_pos_.append("Pos");
  this->id_size_ = name;
  this->id_size_.append("Size");
  this->id_scale_ = name;
  this->id_scale_.append(ID_SCALE);
}

void DesignData::LoadFromJson(JsonNode* node)
{
  JsonNode* n = node->GainNode(this->name_);
  this->anchor_ = n->GainValue(ID_ANCHOR)->IntValue();
  this->pos_[0] = n->GainValue(ID_X)->FloatValue();
  this->pos_[1] = n->GainValue(ID_Y)->FloatValue();
  if (this->size_type_ == SizeType::SIZE)
  {
    this->size_[0] = n->GainValue(ID_WIDTH)->FloatValue();
    this->size_[1] = n->GainValue(ID_HEIGHT)->FloatValue();
  }
  if (this->size_type_ == SizeType::SCALE)
  {
    this->size_[0] = n->GainValue(ID_SCALE)->FloatValue();
  }
}

void DesignData::ToJson(JsonNode* dest)
{
  JsonNode* n = dest->GainNode(this->name_);
  *n->GainValue(ID_ANCHOR) = this->anchor_;
  *n->GainValue(ID_X) = this->pos_[0];
  *n->GainValue(ID_Y) = this->pos_[1];
  if (this->size_type_ == SizeType::SIZE)
  {
    *n->GainValue(ID_WIDTH) = this->size_[0];
    *n->GainValue(ID_HEIGHT) = this->size_[1];
  }
  if (this->size_type_ == SizeType::SCALE)
  {
    *n->GainValue(ID_SCALE) = this->size_[0];
  }
}

bool DesignData::EditWithImgui()
{
  if (ImGui::TreeNode(this->name_.c_str()))
  {
    std::string head = u8" *Anchor";
    if (this->parent_)
    {
      head.append(" ( parent = ");
      head.append(this->parent_->name_);
      head.append(" )");
    }
    ImGui::Text(head.c_str());
    this->is_dirty_ |= ImGui::Combo(this->id_anchor_.c_str(), &this->anchor_, GetAnchorText());
    ImGui::Text(u8" *Position");
    this->is_dirty_ |= ImGui::SliderFloat2(this->id_pos_.c_str(), this->pos_, -0.25f, 0.25f, "%.3f");
    if (this->size_type_ == SizeType::SIZE)
    {
      ImGui::Text(u8" *Size");
      this->is_dirty_ |= ImGui::SliderFloat2(this->id_size_.c_str(), this->size_, 0.0f, 1.0f, "%.2f");
    }
    if (this->size_type_ == SizeType::SCALE)
    {
      ImGui::Text(u8" *Scale");
      this->is_dirty_ |= ImGui::SliderFloat(this->id_scale_.c_str(), &this->size_[0], 0.0f, 1.0f, "%.2f");
    }
    ImGui::TreePop();
  }
  return this->is_dirty_;
}

void DesignData::ResetFlags()
{
  this->is_dirty_ = true;
}

void DesignData::ConvertSize(T_FLOAT width, T_FLOAT height, TAreaf* dest) const
{
  T_FLOAT offset_x = 0.0f;
  T_FLOAT offset_y = 0.0f;
  T_FLOAT parent_width = width;
  T_FLOAT parent_height = height;
  if (this->parent_)
  {
    offset_x = this->parent_->cache_.pos.x;
    offset_y = this->parent_->cache_.pos.y;
    parent_width = this->parent_->cache_.size.width;
    parent_height = this->parent_->cache_.size.height;
  }
  
  T_FLOAT x = offset_x + this->pos_[0] * width;
  T_FLOAT y = offset_y + this->pos_[1] * height;
  T_FLOAT w = 0.0f;
  T_FLOAT h = 0.0f;
  if (this->size_type_ == SizeType::SIZE)
  {
    w = this->size_[0] * width;
    h = this->size_[1] * height;
  }
  if (this->size_type_ == SizeType::SCALE)
  {
    w = h = this->size_[0] * std::min(width, height);
  }
  if (this->anchor_ < Anchor::OUTER_TOP_LEFT)
  {
    const T_UINT8 anchor_x = this->anchor_ % 3;
    const T_UINT8 anchor_y = this->anchor_ / 3;
    const T_FLOAT rx = (anchor_x - 1) * 0.5f;
    const T_FLOAT ry = -(anchor_y - 1) * 0.5f;

    dest->pos.x = x + (parent_width - w) * rx;
    dest->pos.y = y + (parent_height - h) * ry;
    dest->size.width = w;
    dest->size.height = h;
  }
  else
  {
    T_UINT8 anchor = this->anchor_ - Anchor::OUTER_TOP_LEFT;
    if (this->anchor_ >= Anchor::OUTER_CENTER)
    {
      anchor++;
    }
    const T_UINT8 anchor_x = anchor % 3;
    const T_UINT8 anchor_y = anchor / 3;
    const T_FLOAT rx = (anchor_x - 1) * 0.5f;
    const T_FLOAT ry = -(anchor_y - 1) * 0.5f;

    dest->pos.x = x + (parent_width - w + w * 2.0f) * rx - w;
    dest->pos.y = y + (parent_height - h + h * 2.0f) * ry - h;
    dest->size.width = w;
    dest->size.height = h;
  }

  const_cast<DesignData*>(this)->cache_ = *dest;
}
