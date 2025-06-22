#include "engine/GameState.h"
#include "engine/engine.h"
#include "lib/cereal/archives/portable_binary.hpp"
#include <string>

const std::string SAVE_FILE_NAME = "save_data/save.dat";
const std::string EMSCRIPTEN_SAVE_FILE_NAME = "/save_data/save.dat";

class SaveManager
{
public:
  SaveManager();
  SaveManager(const SaveManager&) = delete;
  SaveManager& operator=(const SaveManager&) = delete;
  static SaveManager* Get();

  void LoadSaveState(SaveState& SaveStateData);
  void SaveStateData(SaveState& SaveStateData);

#ifdef __EMSCRIPTEN__
  static void OnSyncfsLoadComplete(void* SaveData, int Success)
  {
    SaveState* SaveStateData = static_cast<SaveState*>(SaveData);

    if (!Success || !SaveStateData)
    {
      std::cout
          << "FS load was unsuccessful, is the persistent storage mounted?"
          << std::endl;
      return;
    }

    std::ifstream InputFileStream(EMSCRIPTEN_SAVE_FILE_NAME, std::ios::binary);
    if (!InputFileStream.is_open())
    {
      std::cout << "Unable to open the file after successful filesystem sync! "
                   "Is the path correct?"
                << std::endl;
      return;
    }

    cereal::PortableBinaryInputArchive archive(InputFileStream);
    archive(*SaveStateData);

    Engine::Get()->GameState->SetGameState(*SaveStateData);
  }
#endif

private:
  static SaveManager* s_instance;
};