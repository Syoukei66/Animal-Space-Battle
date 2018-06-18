#pragma once

#include <vector>
#include "PlayerEntry.h"

/*
  �v���C���[�̎Q���󋵂�ݒ肷��N���X
  �v���C���[�Z���N�g��ʂŗ��p���鎖���ł���
*/

class PlayerEntryList
{
public:
  PlayerEntryList(T_UINT8 entries_count);
  ~PlayerEntryList();

public:
  PlayerEntry* AddEntry(T_UINT8 kind);

  void SetEntry(T_UINT8 id, T_UINT8 kind);
  //�w��h�c�̃v���C���[�̎Q����Ԃ�؂�ւ�
  //�i�v���C���[���R���s���[�^�[���s�Q�����v���C���[���c�Ń��[�v�j
  void IncrementEntryKind(T_UINT8 id);
  //�w��h�c�̃v���C���[�𖢎Q����
  void ResetEntry(T_UINT8 id);

  void ResetEntries();

  PlayerEntry* AddDebugEntity();

protected:
  PlayerEntry* GetEmptyEntry();

public:
  inline PlayerEntry* GetEntry(T_UINT8 id) const
  {
    return this->entries_[id];
  }

  inline T_UINT8 GetEntriesCount() const
  {
    return this->entries_.size();
  }

private:
  //PlayerEntryDataModel���g�������Ă���id�Ɣz���id�͑Ή����Ă���
  std::vector<PlayerEntry*> entries_;
};
