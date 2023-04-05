#include "interface.h"

const std::vector<std::string> Interface::m_menus{
    " -------------------------------------------------------------- \n"
    "|                       Transaction 1.0                        |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|                 Selecting the main container.                |\n"
    " -------------------------------------------------------------- \n"
    "| 1. HASH_TABLE                                                |\n"
    "| 2. B+TREE                                                    |\n"
    "| 3. BINARY_TREE                                               |\n"
    "| 4. Statistics                                                |\n"
    " -------------------------------------------------------------- \n",
    " > ",
    " > OK\n",
    " > true\n",
    " > false\n",
    " > (null)\n",
    " > Not esixt path: ",
    " -------------------------------------------------------------- \n"
    "|                The written command is invalid                |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|                             INFO                             |\n"
    " -------------------------------------------------------------- \n"
    "| 1. SET <ключ> <Фамилия> <Имя> <Год рождения> <Город>         |\n"
    "| <Число текущих коинов> EX <время в секундах>                 |\n"
    "| 2. GET <ключ>                                                |\n"
    "| 3. EXISTS <ключ>                                             |\n"
    "| 4. DEL <ключ>                                                |\n"
    "| 5. UPDATE <ключ> <Фамилия> <Имя> <Год рождения> <Город>      |\n"
    "| <Число текущих коинов>                                       |\n"
    "| 6. KEYS <null>                                               |\n"
    "| 7. RENAME <ключ> <ключ>                                      |\n"
    "| 8. TTL <ключ>                                                |\n"
    "| 9. FIND <Фамилия> <Имя> <Год рождения> <Город>               |\n"
    "| <Число текущих коинов>                                       |\n"
    "| 10. SHOWALL <null>                                           |\n"
    "| 11. UPLOAD <path>                                            |\n"
    "| 12. EXPORT <path>                                            |\n"
    "| 13. INFO <null>                                              |\n"
    "| 14. EXIT <null>                                              |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|                          Statistics                          |\n"
    " -------------------------------------------------------------- \n"
    "|   Opretation   |   HashTable   |   BinaryTree   |   B+Tree   |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|            Successful completion of the programme            |\n"
    " -------------------------------------------------------------- \n"};

Interface::Interface() {
  std::cout << m_menus[MenuItem::kIntroduction];

  m_funcs.emplace("SET",
                  std::bind(&Interface::Set, this, std::placeholders::_1));
  m_funcs.emplace("GET",
                  std::bind(&Interface::Get, this, std::placeholders::_1));
  m_funcs.emplace("EXISTS",
                  std::bind(&Interface::Exists, this, std::placeholders::_1));
  m_funcs.emplace("DEL",
                  std::bind(&Interface::Del, this, std::placeholders::_1));
  m_funcs.emplace("UPDATE",
                  std::bind(&Interface::Update, this, std::placeholders::_1));
  m_funcs.emplace("KEYS",
                  std::bind(&Interface::Keys, this, std::placeholders::_1));
  m_funcs.emplace("RENAME",
                  std::bind(&Interface::Rename, this, std::placeholders::_1));
  m_funcs.emplace("TTL",
                  std::bind(&Interface::TTL, this, std::placeholders::_1));
  m_funcs.emplace("FIND",
                  std::bind(&Interface::Find, this, std::placeholders::_1));
  m_funcs.emplace("SHOWALL",
                  std::bind(&Interface::Showall, this, std::placeholders::_1));
  m_funcs.emplace("UPLOAD",
                  std::bind(&Interface::Upload, this, std::placeholders::_1));
  m_funcs.emplace("EXPORT",
                  std::bind(&Interface::Export, this, std::placeholders::_1));
  m_funcs.emplace("INFO",
                  std::bind(&Interface::Info, this, std::placeholders::_1));
  m_funcs.emplace("EXIT",
                  [](std::istringstream &) -> const bool { return false; });
}

Interface::~Interface() {
  m_ttl.clear();
  for (auto &it : m_threads) {
    it.join();
  }
  std::cout << m_menus[MenuItem::kCompletion];
}

void Interface::Exec() {
  std::cout << m_menus[MenuItem::kSelectContainer];
  std::size_t select = CheckInput(static_cast<std::size_t>(4));
  if (select == 1U) {
    m_container = std::make_unique<s21::HashTable<std::string, s21::Storage>>();
  } else if (select == 2U) {
    m_container = std::make_unique<s21::BPlusTree<std::string, s21::Storage>>();
  } else if (select == 3U) {
    m_container = std::make_unique<
        s21::SelfBalancingBinarySearchTree<std::string, s21::Storage>>();
  } else if (select == 4U) {
    Statistics();
    return;
  }
  for (std::istringstream stream; m_funcs[CheckInput(stream)](stream);
       stream.clear())
    ;
}

const std::size_t Interface::CheckInput(const std::size_t count) const {
  std::cout << m_menus[MenuItem::kInput];

  std::string line;
  std::getline(std::cin, line);

  std::size_t result;
  while (!sscanf(line.c_str(), "%zu", &result) || result > count) {
    std::cout << m_menus[MenuItem::kInvalid];
    std::cout << m_menus[MenuItem::kInput];
    std::getline(std::cin, line);
  }
  return result;
}

const std::string Interface::CheckInput(std::istringstream &stream) {
  std::cout << m_menus[MenuItem::kInput];

  static const std::vector<std::regex> regex{
      std::regex(
          R"(^(UPDATE)\s+(\w{1,15}|[-])\s+(\S+|[-])\s+(\S+|[-])\s+(\d{4}|[-])\s+(\S+|[-])\s+(\d+|[-])(\s+)?$)"),
      std::regex(
          R"(^FIND\s+(\S+|[\-])\s+(\S+|[\-])\s+(\d{4}|[\-])\s+(\S+|[\-])\s+(\d{4}|[\-])(\s+)?$)"),
      std::regex(
          R"(^SET\s+\w{1,15}\s+\S+\s+\S+\s+\d{4}\s+\S+\s+\d+(\s+EX\s+\d+)?(\s+)?$)"),
      std::regex(R"(^(UPLOAD|EXPORT)\s+\S+(\s+)?$)"),
      std::regex(R"(^(GET|EXISTS|DEL|TTL)\s+\S+$)"),
      std::regex(R"(^(RENAME)\s+\S+\s+\S+(\s+)?$)"),
      std::regex(R"(^(KEYS|SHOWALL|EXIT|INFO)$)")};

  std::string line;
  while (std::getline(std::cin, line) &&
         std::find_if(regex.begin(), regex.end(), [&](const std::regex &src) {
           return std::regex_match(line, src);
         }) == regex.end()) {
    std::cout << m_menus[MenuItem::kInvalid];
    std::cout << m_menus[MenuItem::kInput];
  }
  stream.str(line);
  stream >> line;
  return line;
}

[[nodiscard]] const bool Interface::Set(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::size_t seconds;
  std::string key, ex;
  s21::Storage storage;

  stream >> key;
  stream >> storage;
  if (stream >> ex >> seconds) {
    storage.SetRemovalTime(std::chrono::seconds(seconds));
  }

  if (m_container->Set(key, storage)) {
    SetTTL(storage, key);
    std::cout << m_menus[MenuItem::kSuccess];
  } else {
    std::cout << m_menus[MenuItem::kFalse];
  }
  return true;
}

[[nodiscard]] const bool Interface::Get(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::string key;
  stream >> key;

  auto storage{m_container->Get(key)};
  if (storage.has_value()) {
    std::cout << storage.value() << "\n";
  } else {
    std::cout << m_menus[MenuItem::kNull];
  }
  return true;
}

[[nodiscard]] const bool Interface::Exists(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::string key;
  stream >> key;

  if (m_container->Exists(key)) {
    std::cout << m_menus[MenuItem::kTrue];
  } else {
    std::cout << m_menus[MenuItem::kFalse];
  }

  return true;
}

[[nodiscard]] const bool Interface::Del(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::string key;
  stream >> key;

  if (m_container->Del(key)) {
    std::cout << m_menus[MenuItem::kTrue];
  } else {
    std::cout << m_menus[MenuItem::kFalse];
  }

  return true;
}

[[nodiscard]] const bool Interface::Update(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::string key;
  s21::Storage storage;

  stream >> key;
  stream >> storage;

  if (m_container->Update(key, storage)) {
    std::cout << m_menus[MenuItem::kSuccess];
  }

  return true;
}

[[nodiscard]] const bool Interface::Keys(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::size_t iteration{};
  for (auto &it : m_container->Keys()) {
    std::cout << ++iteration << ") " << it << "\n";
  }
  return true;
}

[[nodiscard]] const bool Interface::Rename(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::string key, rename;
  stream >> key >> rename;

  if (m_container->Rename(key, rename)) {
    std::cout << m_menus[MenuItem::kSuccess];
  } else {
    std::cout << m_menus[MenuItem::kNull];
  }

  return true;
}

[[nodiscard]] const bool Interface::TTL(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::string key;
  stream >> key;

  auto ttl{m_container->TTL(key)};
  if (ttl.has_value()) {
    std::cout << " > " << ttl.value() << "\n";
  } else {
    std::cout << m_menus[MenuItem::kNull];
  }

  return true;
}

[[nodiscard]] const bool Interface::Find(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  s21::Storage storage;
  stream >> storage;

  std::size_t iteration{};
  for (auto &it : m_container->Find(storage)) {
    std::cout << ++iteration << ") " << it << "\n";
  }

  return true;
}

[[nodiscard]] const bool Interface::Showall(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::cout << std::left;
  std::cout << "> № ";
  std::cout << std::setw(14) << "Surname";
  std::cout << std::setw(14) << "Name";
  std::cout << std::setw(14) << "Year";
  std::cout << std::setw(16) << "Sity";
  std::cout << std::setw(5) << "Coins";
  std::cout << "\n";

  m_container->Showall();
  return true;
}

[[nodiscard]] const bool Interface::Upload(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::filesystem::path path;
  stream >> path;

  if (std::filesystem::exists(path)) {
    std::ifstream is(path.native());
    std::cout << m_menus[MenuItem::kSuccess] << m_container->Upload(is);
  } else {
    std::cout << m_menus[MenuItem::kNotExist] << path << "\n";
  }
  return true;
}

[[nodiscard]] const bool Interface::Export(std::istringstream &stream) {
  std::lock_guard<std::mutex> lock(m_mutex);
  std::filesystem::path path;
  stream >> path;

  if (std::filesystem::exists(path)) {
    std::ofstream os(path.native());
    std::cout << m_menus[MenuItem::kSuccess] << m_container->Export(os);
  } else {
    std::cout << m_menus[MenuItem::kNotExist] << path << "\n";
  }
  return true;
}

[[nodiscard]] const bool Interface::Info(std::istringstream &stream) {
  std::cout << m_menus[MenuItem::kInfo];
  return true;
}

void Interface::SetTTL(const s21::Storage &storage, const std::string &key) {
  auto tp = storage.GetRemovalTime();
  if (tp.has_value()) {
    m_ttl.emplace(tp.value(), key);
    if (m_ttl.size() == 1) {
      m_threads.emplace_back(std::thread([this]() -> void {
        while (m_ttl.size()) {
          auto time = std::chrono::steady_clock::now();
          for (auto it = m_ttl.begin();
               it != m_ttl.end() && time > it->first;) {
            m_container->Del(it->second);
            m_ttl.erase(it++);
          }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }));
    }
  }
}

void Interface::Statistics() {
  vector_container containers;
  containers.emplace_back(
      std::make_unique<s21::HashTable<std::string, s21::Storage>>());
  containers.emplace_back(
      std::make_unique<
          s21::SelfBalancingBinarySearchTree<std::string, s21::Storage>>());
  containers.emplace_back(
      std::make_unique<s21::BPlusTree<std::string, s21::Storage>>());

  std::cout << "Enter count elements";
  std::size_t countElements = CheckInput(static_cast<std::size_t>(100000));
  std::cout << "Enter count repeat";
  std::size_t countRepeat = CheckInput(static_cast<std::size_t>(countElements));

  FillRandonly(containers, countElements);
  auto result = GetResults(containers, countRepeat);

  std::vector<std::string> commands = {"      GET       ", "      SET       ",
                                       "      DEL       ", "      KEYS      ",
                                       "      FIND      "};
  std::vector<int> column_width{15, 16, 12};
  std::cout << m_menus[MenuItem::kStatistics];
  for (int i = 0; i < 5; ++i) {
    std::cout << "|" << commands[i] << "|";
    for (int j = 0; j < 3; ++j) {
      std::cout << std::setw(column_width[j]) << result[i * 3 + j] << "|";
    }
    std::cout << std::endl;
  }
}

int Interface::RandomInRange(int start, int end) {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(start, end);
  return dist(engine);
}

std::istringstream Interface::CreateRecord(int key) {
  int min = std::numeric_limits<int>::min();
  int max = std::numeric_limits<int>::max();

  std::stringstream stream;
  stream << key << " " << RandomInRange(min, max) << " ";
  stream << RandomInRange(min, max) << " " << RandomInRange(1970, 2004) << " ";
  stream << RandomInRange(0, 10) << " " << RandomInRange(0, 10000);
  std::istringstream istream(stream.str());

  return istream;
}

void Interface::FillRandonly(vector_container &containers, std::size_t count) {
  for (int i = 0; i < count; ++i) {
    auto stream = CreateRecord(i);
    std::string key;
    s21::Storage storage;
    stream >> key;
    stream >> storage;
    containers[0]->Set(key, storage);
    containers[1]->Set(key, storage);
    containers[2]->Set(key, storage);
  }
}

std::vector<double> Interface::GetResults(vector_container &containers,
                                          std::size_t countRepeat) {
  std::vector<double> result(15);
  TestGet(containers, countRepeat, result);
  TestSet(containers, countRepeat, result);
  TestDel(containers, countRepeat, result);
  TestKeys(containers, countRepeat, result);
  TestFind(containers, countRepeat, result);

  return result;
}

void Interface::TestGet(vector_container &containers, std::size_t countRepeat,
                        std::vector<double> &result) {
  time_sc::time_point start, end;
  for (int i = 0; i < countRepeat; ++i) {
    std::string key =
        std::to_string(RandomInRange(1, containers[0]->GetAmountElements()));
    for (int j = 0; j < containers.size(); ++j) {
      start = time_sc::now();
      auto temp = containers[j]->Get(key);
      end = time_sc::now();
      result[j] += std::chrono::duration<double>(end - start).count();
    }
  }
}

void Interface::TestSet(vector_container &containers, std::size_t countRepeat,
                        std::vector<double> &result) {
  time_sc::time_point start, end;
  for (int i = 0; i < countRepeat; ++i) {
    auto stream = CreateRecord(containers[0]->GetAmountElements());
    std::string key;
    s21::Storage storage;
    stream >> key;
    stream >> storage;
    for (int j = 0; j < containers.size(); ++j) {
      start = time_sc::now();
      containers[j]->Set(key, storage);
      end = time_sc::now();
      result[3 + j] += std::chrono::duration<double>(end - start).count();
    }
  }
}

void Interface::TestDel(vector_container &containers, std::size_t countRepeat,
                        std::vector<double> &result) {
  time_sc::time_point start, end;
  for (int i = 0; i < countRepeat; ++i) {
    std::string key = std::to_string(containers[0]->GetAmountElements() - 1);
    for (int j = 0; j < containers.size(); ++j) {
      start = time_sc::now();
      containers[j]->Del(key);
      end = time_sc::now();
      result[6 + j] += std::chrono::duration<double>(end - start).count();
    }
  }
}

void Interface::TestKeys(vector_container &containers, std::size_t countRepeat,
                         std::vector<double> &result) {
  time_sc::time_point start, end;
  for (int i = 0; i < countRepeat; ++i) {
    for (int j = 0; j < containers.size(); ++j) {
      start = time_sc::now();
      auto trash = containers[j]->Keys();
      end = time_sc::now();
      result[9 + j] += std::chrono::duration<double>(end - start).count();
    }
  }
}

void Interface::TestFind(vector_container &containers, std::size_t countRepeat,
                         std::vector<double> &result) {
  time_sc::time_point start, end;
  for (int i = 0; i < countRepeat; ++i) {
    std::string key =
        std::to_string(RandomInRange(1, containers[0]->GetAmountElements()));
    std::optional<s21::Storage> temp = containers[0]->Get(key);
    for (int j = 0; j < containers.size(); ++j) {
      start = time_sc::now();
      auto _ = containers[j]->Find(temp.value());
      end = time_sc::now();
      result[12 + j] += std::chrono::duration<double>(end - start).count();
    }
  }
}
