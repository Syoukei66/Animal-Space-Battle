#include "PlayerView.h"
#include "Player.h"
#include "GameLayer.h"
#include "ViewportSetting.h"
#include "PlayerManager.h"

static const T_FLOAT CAMERA_Y = 5.0f;
static const T_FLOAT CAMERA_Y_RADIUS_RATE = 1.5f;
static const T_FLOAT CAMERA_Z = -8.0f;
static const T_FLOAT CAMERA_Z_RADIUS_RATE = -5.0f;

PlayerView* PlayerView::Create(Player* player)
{
  return new PlayerView(player);
}

PlayerView::PlayerView(Player* player)
  : player_(player)
  , render_target_(nullptr)
{
  const T_UINT8 layer_id = player->GetID() + GameLayer::LAYER_PLAYER_0;
  this->ui_ = new PlayerUI(player);
  this->ui_->SetVisible(false);
  this->ui_->SetAllLayerId(layer_id);
  
  this->ui_camera_ = new Camera2D();
  this->ui_camera_->SetViewportClear(true);
  this->ui_camera_->SetEnabled(false);
  this->ui_camera_->GetRenderState()->AddTargetLayerId(layer_id);

  this->player_camera_ = new Camera3D_LookAt();
  this->player_camera_->SetEnabled(false);
  this->player_camera_->SetPlayer(player);
  this->player_camera_->SetZNear(1.0f);
  this->player_camera_->SetZFar(2000.0f);

  this->view_3d_ = Sprite::Create();
  this->view_3d_->SetLayerId(layer_id);

  this->post_effect_ = Asset::Material::POST_EFFECT.Clone();
  this->post_effect_->TextureProperty("_NoiseTexture") = Asset::Texture::SHADER_NOISE.GetContents();
  this->view_3d_->SetMaterial(*this->post_effect_);

  this->GameViewMode();
}

PlayerView::~PlayerView()
{
  delete this->view_3d_;
  delete this->render_target_;
  delete this->player_camera_;
  delete this->ui_camera_;
  delete this->ui_;
}

void PlayerView::AttachAdditionToScene(Scene* scene)
{
  scene->AddChild(this->view_3d_);
  scene->AddChild(this->ui_);
  scene->AddCamera(this->ui_camera_);
  scene->AddCamera(this->player_camera_);
}

void PlayerView::DetachAdditionFromScene(Scene* scene)
{
  this->view_3d_->RemoveSelf();
  this->ui_->RemoveSelf();
  scene->RemoveCamera(this->ui_camera_);
  scene->RemoveCamera(this->player_camera_);
}

void PlayerView::GachaCountDown(T_INT32 left_time)
{
  this->ui_->GachaCountDown(left_time);
}

void PlayerView::OnDead()
{
  this->ui_->OnDead();
}

void PlayerView::GameViewMode()
{
  this->ui_->GameViewMode();
  this->player_camera_->GetRenderState()->ClearTargetLayerIds();
  this->player_camera_->GetRenderState()->AddTargetLayerId(0);
  const T_UINT8 layer_id = this->player_->GetID() + GameLayer::LAYER_PLAYER_0;
  this->player_camera_->GetRenderState()->AddTargetLayerId(layer_id);
  const T_UINT8 player_count = PlayerManager::GetInstance().GetPlayerCount();
  for (T_UINT8 i = 0; i < player_count; ++i)
  {
    this->player_camera_->GetRenderState()->AddTargetLayerId(GameLayer::LAYER_PLAYER_0_BODY + i);
  }
}

void PlayerView::GachaViewMode()
{
  this->ui_->GachaViewMode();
  this->player_camera_->GetRenderState()->ClearTargetLayerIds();
  const T_UINT8 id = this->player_->GetID();
  this->player_camera_->GetRenderState()->AddTargetLayerId(GameLayer::LAYER_PLAYER_0 + id);
  this->player_camera_->GetRenderState()->AddTargetLayerId(GameLayer::LAYER_PLAYER_0_BODY + id);
}

void PlayerView::ViewportUpdate()
{
  if (ViewportSetting::GetInstance().IsDirty())
  {
    const PlayerCameraViewport& viewport = ViewportSetting::GetInstance().GetViewport(this->player_->GetID());
    this->ui_camera_->SetEnabled(viewport.enabled);
    this->ui_->SetVisible(viewport.enabled);
    this->player_camera_->SetEnabled(viewport.enabled);
    if (viewport.enabled)
    {
      this->ui_camera_->SetViewportPosition(viewport.area.pos);
      this->ui_camera_->SetViewportSize(viewport.area.size);
      //this->player_camera_->SetViewportPosition(viewport.area.pos);
      this->player_camera_->SetViewportSize(viewport.area.size);
      this->post_effect_->IntProperty("_PixelX") = (T_INT32)viewport.area.size.width;
      this->post_effect_->IntProperty("_PixelY") = (T_INT32)viewport.area.size.height;

      if (this->render_target_)
      {
        delete this->render_target_;
      }
      this->render_target_ = INativeRenderTexture::Create(viewport.area.size.width, viewport.area.size.height, INativeRenderTexture::TEXTURE_FORMAT_R16G16B16A16F);
      this->view_3d_->SetTexture(this->render_target_);
      this->view_3d_->FitToTexture();
      this->player_camera_->SetTargetTexture(this->render_target_);
    }
  }
  T_FLOAT radius = this->player_->GetColliderRadius();
  TVec3f next = TVec3f();
  next.y = CAMERA_Y + CAMERA_Y_RADIUS_RATE * radius;
  next.z = CAMERA_Z + CAMERA_Z_RADIUS_RATE * radius;
  this->player_camera_->GetTransform()->SetPosition(TVec3f::Lerp(this->player_camera_->GetTransform()->GetPosition(), next, 0.1f));

  if (this->ui_camera_->IsEnabled())
  {
    this->ui_->UiUpdate(this->ui_camera_, this->player_camera_);
  }

  this->post_effect_->FloatProperty("_Time") = HalEngine::Time::ElapsedFrameSinceSceneCreate() / 60.0f / 20.0f;
}

