#ifndef TRANSACTION_SRC_INTERFACE_INTERFACE_H_
#define TRANSACTION_SRC_INTERFACE_INTERFACE_H_

#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <mutex>
#include <random>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>

#include "b_plus_tree.h"
#include "hash_table.h"
#include "self_balancing_binary_search_tree.h"

class Interface {
 public:
  Interface();
  ~Interface();

  void Exec();

 private:
  enum MenuItem {
    kIntroduction = 0,
    kSelectContainer,
    kInput,
    kSuccess,
    kTrue,
    kFalse,
    kNull,
    kNotExist,
    kInvalid,
    kInfo,
    kStatistics,
    kCompletion
  };

  using fp_1arg = std::function<const bool(std::istringstream &)>;

  static const std::vector<std::string> m_menus;
  std::unordered_map<std::string, fp_1arg> m_funcs;

  std::unique_ptr<s21::AbstractContainer<std::string, s21::Storage>>
      m_container;

  std::map<std::chrono::steady_clock::time_point, std::string> m_ttl;
  std::vector<std::thread> m_threads;
  std::mutex m_mutex;

  const std::size_t CheckInput(const std::size_t count) const;
  const std::string CheckInput(std::istringstream &stream);

  [[nodiscard]] const bool Set(std::istringstream &stream);
  [[nodiscard]] const bool Get(std::istringstream &stream);
  [[nodiscard]] const bool Exists(std::istringstream &stream);
  [[nodiscard]] const bool Del(std::istringstream &stream);
  [[nodiscard]] const bool Update(std::istringstream &stream);
  [[nodiscard]] const bool Keys(std::istringstream &stream);
  [[nodiscard]] const bool Rename(std::istringstream &stream);
  [[nodiscard]] const bool TTL(std::istringstream &stream);
  [[nodiscard]] const bool Find(std::istringstream &stream);
  [[nodiscard]] const bool Showall(std::istringstream &stream);
  [[nodiscard]] const bool Upload(std::istringstream &stream);
  [[nodiscard]] const bool Export(std::istringstream &stream);
  [[nodiscard]] const bool Info(std::istringstream &stream);

  void SetTTL(const s21::Storage &storage, const std::string &key);

  using vector_container = std::vector<
      std::unique_ptr<s21::AbstractContainer<std::string, s21::Storage>>>;
  using ms = std::chrono::milliseconds;
  using time_sc = std::chrono::steady_clock;

  void Statistics();
  int RandomInRange(int, int);
  [[nodiscard]] std::istringstream CreateRecord(int key);
  void FillRandonly(vector_container &, std::size_t);
  [[nodiscard]] std::vector<double> GetResults(vector_container &,
                                               std::size_t countRepeat);
  void TestGet(vector_container &, std::size_t, std::vector<double> &);
  void TestSet(vector_container &, std::size_t, std::vector<double> &);
  void TestDel(vector_container &, std::size_t, std::vector<double> &);
  void TestKeys(vector_container &, std::size_t, std::vector<double> &);
  void TestFind(vector_container &, std::size_t, std::vector<double> &);
};

#endif  // TRANSACTION_SRC_INTERFACE_INTERFACE_H_