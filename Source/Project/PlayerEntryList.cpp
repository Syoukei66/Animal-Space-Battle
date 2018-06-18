#include "PlayerEntryList.h"

PlayerEntryList::PlayerEntryList(T_UINT8 entries_count)
  : entries_()
{
  for (T_UINT8 i = 0; i < entries_count; ++i)
  {
    this->entries_.push_back(new PlayerEntry(i));
  }
}

PlayerEntryList::~PlayerEntryList()
{
  for (PlayerEntry* entry : this->entries_)
  {
    delete entry;
  }
}

PlayerEntry* PlayerEntryList::AddEntry(T_UINT8 kind)
{
  PlayerEntry* new_entry = GetEmptyEntry();
  if (!new_entry)
  {
    return nullptr;
  }
  new_entry->entry_kind = kind;
  return new_entry;
}

void PlayerEntryList::SetEntry(T_UINT8 id, T_UINT8 kind)
{
  this->entries_[id]->entry_kind = kind;
}

void PlayerEntryList::IncrementEntryKind(T_UINT8 id)
{
  const T_UINT8 kind = (this->entries_[id]->entry_kind + 1) % PlayerEntry::PLAYER_ENTRY_DATANUM;
  this->entries_[id]->entry_kind = kind;
}

void PlayerEntryList::ResetEntry(T_UINT8 id)
{
  this->entries_[id]->entry_kind = PlayerEntry::PLAYER_ENTRY_NONE;
  this->entries_[id]->animal_data = nullptr;
  this->entries_[id]->handicap = 0;
}

void PlayerEntryList::ResetEntries()
{
  for (PlayerEntry* entry : this->entries_)
  {
    this->ResetEntry(entry->id);
  }
}

PlayerEntry* PlayerEntryList::AddDebugEntity()
{
  PlayerEntry* entry = new PlayerEntry(this->entries_.size());
  entry->entry_kind = PlayerEntry::PLAYER_ENTRY_DEBUG;
  this->entries_.push_back(entry);
  return entry;
}

PlayerEntry* PlayerEntryList::GetEmptyEntry()
{
  for (PlayerEntry* entry : this->entries_)
  {
    if (entry->entry_kind == PlayerEntry::PLAYER_ENTRY_NONE)
    {
      return entry;
    }
  }
  return nullptr;
}
