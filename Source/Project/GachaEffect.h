#pragma once

class GachaEffect : public GameObject3D
{
public:
  GachaEffect();
  ~GachaEffect();

public:
  void SetLayerIdForAll(T_UINT8 id);
  void EffectBegin();
  void Update() override;

private:
  Model* wall_;
  Model* jet_effect_;
  Model* sphare_effect_;

  T_UINT32 gacha_time_count_;

};