#include "DevelopParamEditor.h"

DevelopParamEditor::DevelopParamEditor(DevelopParam* param, const char* directory_path, const char* file_path)
  : param_(param)
  , directory_path_()
  , file_path_()
{
  strcpy_s(this->directory_path_, directory_path);
  strcpy_s(this->file_path_, file_path);
}

void DevelopParamEditor::Update()
{
  this->param_->EditWithImgui();
  ImVec2 winpos = ImVec2(800, 20);
  ImVec2 winsize = ImVec2(400, 120);

  ImGui::SetNextWindowPos(winpos, ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(winsize, ImGuiSetCond_Once);
  ImGui::Begin(u8"出力メニュー");
  ImGui::InputText(u8"出力ディレクトリ", this->directory_path_, sizeof(this->directory_path_));
  ImGui::InputText(u8"ファイル名", this->file_path_, sizeof(this->file_path_));
  ImGui::Text(u8"※.jsonは付けなくていいです");
  if (ImGui::Button(u8"出力", ImVec2(100, 20)))
  {
    JsonNode* root = JsonNode::CreateRoot();
    this->param_->ToJson(root);
    std::string file_path = this->directory_path_;
    file_path.append("/");
    file_path.append(this->file_path_);
    file_path.append(".json");
    NativeMethod::IO().TextFile_Write(file_path.c_str(), root->ToString());
    root->Release();
  }
  ImGui::End();
}
