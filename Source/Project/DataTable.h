#pragma once

#include <map>
#include <string>

template<class T>
class DataTable
{
protected:
  DataTable(const std::string& csv_path)
    : csv_path_(csv_path)
  {}
  DataTable(const DataTable& b) = delete;

public:
  virtual ~DataTable() {}

public:
  void Load()
  {
    CSVResource* csv = CSVResource::DynamicLoad(this->csv_path_.c_str());
    CSVData* csv_data = csv->GetContents();
    this->data_count_ = csv_data->GetTokenizerCount();
    this->datas_ = new const T*[this->data_count_];
    for (T_UINT8 i = 0; i < this->data_count_; ++i)
    {
      CSVTokenizer tokenizer = csv_data->GetTokenizer(i);
      const T* data = T::Create(tokenizer);
      this->datas_[i] = data;
      this->name_indexed_datas_[data->GetNameId()] = data;
    }
    csv->Release();
  }
  void Unload()
  {
    for (T_UINT8 i = 0; i < this->data_count_; ++i)
    {
      delete this->datas_[i];
    }
    delete[] this->datas_;
    this->data_count_ = 0;
  }
public:
  inline T_UINT8 GetDataCount() const
  {
    return this->data_count_;
  }
  inline const T* GetData(T_UINT8 id) const
  {
    return this->datas_[id];
  }
  inline const T* GetDataByNameId(const std::string& name_id) const
  {
    return this->name_indexed_datas_.at(name_id);
  }

private:
  const std::string csv_path_;
  const T** datas_;
  std::map<std::string, const T*> name_indexed_datas_;
  T_UINT8 data_count_;
};