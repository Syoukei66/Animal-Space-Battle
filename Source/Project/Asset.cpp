#include "Asset.h"

namespace Asset
{

namespace Texture
{
TextureResource FONT_NUMBER("Asset/Texture/font/number.png");
TextureResource FONT_NUMBER__UNKKODAF("Asset/Texture/font/number -unkkodaf.png");
TextureResource SHADER_NOISE("Asset/Texture/shader/Noise.png");
TextureResource SHADER_NOISE_NORMAL("Asset/Texture/shader/NoiseNormal.png");
TextureResource SHADER_NOISE_NORMAL1("Asset/Texture/shader/NoiseNormal1.png");
TextureResource TEST_BULLET("Asset/Texture/test/bullet.png");
TextureResource UI_1P("Asset/Texture/ui/1p.png");
TextureResource UI_2P("Asset/Texture/ui/2p.png");
TextureResource UI_3P("Asset/Texture/ui/3p.png");
TextureResource UI_4P("Asset/Texture/ui/4p.png");
TextureResource UI_CHAR_BACK("Asset/Texture/ui/char_back.png");
TextureResource UI_CHAR_BACK2("Asset/Texture/ui/char_back2.png");
TextureResource UI_CHAR_BACK3("Asset/Texture/ui/char_back3.png");
TextureResource UI_CHAR_BACK4("Asset/Texture/ui/char_back4.png");
TextureResource UI_CHAR_BACK_CP("Asset/Texture/ui/char_back_cp.png");
TextureResource UI_CHAR_BACK_CP_RANDOM("Asset/Texture/ui/char_back_cp_random.png");
TextureResource UI_CHAR_BACK_NOT("Asset/Texture/ui/char_back_not.png");
TextureResource UI_CHAR_SELECT_BACK_GROUND("Asset/Texture/ui/char_select_back_ground.png");
TextureResource UI_CHAR_SELECT_BACK_GROUND2("Asset/Texture/ui/char_select_back_ground2.png");
TextureResource UI_CURSOR("Asset/Texture/ui/cursor.png");
TextureResource UI_GAME_ANIMAL_ICON_BG("Asset/Texture/ui/game/animal_icon_bg.png");
TextureResource UI_GAME_BG("Asset/Texture/ui/game/bg.png");
TextureResource UI_GAME_COUNT_MESSAGE("Asset/Texture/ui/game/count_message.png");
TextureResource UI_GAME_COUNT_NUMBER("Asset/Texture/ui/game/count_number.png");
TextureResource UI_GAME_HP_GAUGE("Asset/Texture/ui/game/hp_gauge.png");
TextureResource UI_GAME_HP_GAUGE_FRAME("Asset/Texture/ui/game/hp_gauge_frame.png");
TextureResource UI_GAME_LOCKON("Asset/Texture/ui/game/lockon.png");
TextureResource UI_GAME_NUMBER("Asset/Texture/ui/game/number.png");
TextureResource UI_GAME_NUMBER_DOT("Asset/Texture/ui/game/number_dot.png");
TextureResource UI_GAME_NUMBER_PLANE("Asset/Texture/ui/game/number_plane.png");
TextureResource UI_GAME_RANK_RANK1("Asset/Texture/ui/game/rank/rank1.png");
TextureResource UI_GAME_RANK_RANK1_KAI("Asset/Texture/ui/game/rank/rank1_kai.png");
TextureResource UI_GAME_RANK_RANK2("Asset/Texture/ui/game/rank/rank2.png");
TextureResource UI_GAME_RANK_RANK3("Asset/Texture/ui/game/rank/rank3.png");
TextureResource UI_GAME_RANK_RANK4("Asset/Texture/ui/game/rank/rank4.png");
TextureResource UI_GAME_VEHICLE_ICON_BG("Asset/Texture/ui/game/vehicle_icon_bg.png");
TextureResource UI_GREEN("Asset/Texture/ui/green.jpg");
TextureResource UI_KAERU("Asset/Texture/ui/kaeru.png");
TextureResource UI_MARU("Asset/Texture/ui/maru.png");
TextureResource UI_NEKO("Asset/Texture/ui/neko.png");
TextureResource UI_PLAYER_1("Asset/Texture/ui/player/1.png");
TextureResource UI_PLAYER_1P("Asset/Texture/ui/player/1P.png");
TextureResource UI_PLAYER_2P("Asset/Texture/ui/player/2P.png");
TextureResource UI_PLAYER_3P("Asset/Texture/ui/player/3P.png");
TextureResource UI_PLAYER_4P("Asset/Texture/ui/player/4P.png");
TextureResource UI_PLAYER_ID("Asset/Texture/ui/player_id.png");
TextureResource UI_TEXT_CREDIT("Asset/Texture/ui/text_credit.png");
TextureResource UI_TEXT_GAME("Asset/Texture/ui/text_game.png");
TextureResource UI_TEXT_HITORI("Asset/Texture/ui/text_hitori.png");
TextureResource UI_TEXT_MINNA("Asset/Texture/ui/text_minna.png");
TextureResource UI_TEXT_PRESSXBUTTON("Asset/Texture/ui/text_pressxbutton.png");
TextureResource UI_TEXT_SETTING("Asset/Texture/ui/text_setting.png");
TextureResource UI_TITLE("Asset/Texture/ui/title.png");
TextureResource UI_TITLE_CHARACTOR("Asset/Texture/ui/title_charactor.png");
TextureResource UI_TITLE_MESSAGE("Asset/Texture/ui/title_message.png");
TextureResource UI_UMA("Asset/Texture/ui/uma.png");
TextureResource UI_USAGI("Asset/Texture/ui/usagi.png");
TextureResource UI_WHITE("Asset/Texture/ui/white.jpg");
} // namespace Texture

namespace Shader
{
ShaderResource COLLIDER("Asset/Shader/Collider.cso");
ShaderResource GACHA_JET("Asset/Shader/GachaJet.cso");
ShaderResource GACHA_STAR("Asset/Shader/GachaStar.cso");
ShaderResource GACHA_WORLD("Asset/Shader/GachaWorld.cso");
ShaderResource JET("Asset/Shader/Jet.cso");
ShaderResource PLAYER_EYE_LINE("Asset/Shader/PlayerEyeLine.cso");
ShaderResource POST_EFFECT("Asset/Shader/PostEffect.cso");
ShaderResource SPACE_GRID("Asset/Shader/SpaceGrid.cso");
ShaderResource SPACE_WALL("Asset/Shader/SpaceWall.cso");
ShaderResource STAR("Asset/Shader/Star.cso");
ShaderResource STAR_WALL("Asset/Shader/StarWall.cso");
} // namespace Shader

namespace Material
{
class Material COLLIDER(Shader::COLLIDER);
class Material GACHA_JET(Shader::GACHA_JET);
class Material GACHA_STAR(Shader::GACHA_STAR);
class Material GACHA_WORLD(Shader::GACHA_WORLD);
class Material JET(Shader::JET);
class Material PLAYER_EYE_LINE(Shader::PLAYER_EYE_LINE);
class Material POST_EFFECT(Shader::POST_EFFECT);
class Material SPACE_GRID(Shader::SPACE_GRID);
class Material SPACE_WALL(Shader::SPACE_WALL);
class Material STAR(Shader::STAR);
class Material STAR_WALL(Shader::STAR_WALL);
} // namespace Material

namespace Fbx
{
FbxResource JET("Asset/Fbx/jet/jet.fbx");
FbxResource PLAYER_EYE_LINE("Asset/Fbx/player_eye_line/silinder.fbx");
FbxResource SKYDOME("Asset/Fbx/skydome/skydome.fbx");
FbxResource SPACE_WALL("Asset/Fbx/space_wall/skydome.fbx");
FbxResource STAR("Asset/Fbx/star/TestStar.fbx");
} // namespace Fbx

namespace Model
{
ModelData SKYBOX("Asset/Model/skybox/skybox.x");
} // namespace Model

namespace Json
{
JsonResource GAME_LEVEL("Asset/Json/GameLevel.json");
JsonResource GAME_SCENE_VISUAL("Asset/Json/GameSceneVisual.json");
JsonResource GAME_UI("Asset/Json/GameUI.json");
} // namespace Json

namespace Sound
{
SoundResource BARRIER("Asset/Sound/barrier.wav");
SoundResource BGM_GAME("Asset/Sound/bgm/game.wav");
SoundResource DAMAGE("Asset/Sound/damage.wav");
SoundResource FLAG("Asset/Sound/flag.wav");
SoundResource OTO("Asset/Sound/oto.wav");
SoundResource SHOT_SHOT_CIRCLE("Asset/Sound/shot/shot_circle.wav");
SoundResource SHOT_SHOT_SANDAN("Asset/Sound/shot/shot_sandan.wav");
SoundResource SHOT_SHOT_WAY("Asset/Sound/shot/shot_way.wav");
SoundResource SHOT_SHOT_ZIBAKU("Asset/Sound/shot/shot_zibaku.wav");
} // namespace Sound

} // namespace Asset
