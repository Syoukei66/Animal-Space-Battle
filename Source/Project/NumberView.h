#pragma once

class NumberView : public GameObject2D
{
public:
  NumberView(T_UINT8 digit_count);
  ~NumberView();

public:
  void SetAllLayerId(T_UINT8 id);
  void ViewInit(T_UINT32 value);
  void Update();

public:
  void SetValue(T_UINT32 value);
  void AnimationFinish();

private:
  void OnUpdateView();

public:
  void SetSize(T_FLOAT width, T_FLOAT height);
  inline const T_UINT32 GetValue() const
  {
    return (T_UINT32)this->value_;
  }
  inline bool IsAnimated() const
  {
    return this->value_ != this->display_value_;
  }
  inline void SetDuration(T_UINT16 duration)
  {
    this->duration_ = duration;
  }

private:
  const T_UINT8 digit_count_;
  TSizef size_;
  T_FLOAT display_value_;
  T_FLOAT value_;
  T_FLOAT count_value_;
  T_UINT16 duration_;
  AnimatedSprite** sprites_;
};