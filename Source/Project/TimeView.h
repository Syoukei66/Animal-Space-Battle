#pragma once

class TimeView : public GameObject2D
{
public:
  TimeView();
  ~TimeView();

public:
  void SetAllLayerId(T_UINT8 id);
  void ViewInit(T_UINT32 millisecond);
  void SetValule(T_UINT32 millisecond);

public:
  void Update() override;

private:
  void OnUpdateView();

public:
  void SetSize(T_FLOAT width, T_FLOAT height);

public:
  inline T_FLOAT GetValue() const
  {
    return this->value_;
  }

private:
  TSizef size_;
  T_FLOAT value_;

  AnimatedSprite* minutes_dot_;
  AnimatedSprite* second_dot_;

  AnimatedSprite* minutes_[2];
  AnimatedSprite* second_[2];
  AnimatedSprite* millisecond_[2];
};