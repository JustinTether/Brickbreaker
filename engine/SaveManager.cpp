#include "SaveManager.h"
#include <fstream>

SaveManager* SaveManager::s_instance = nullptr;

SaveManager::SaveManager() {}

SaveManager* SaveManager::Get()
{
  if (s_instance == nullptr)
  {
    s_instance = new SaveManager();
  }

  return s_instance;
}

#ifdef __EMSCRIPTEN__
extern "C"
{
  EMSCRIPTEN_KEEPALIVE
  void C_SaveManager_OnSyncfsLoadComplete(void* SaveData, int Success)
  {
    SaveManager::OnSyncfsLoadComplete(SaveData, Success);
  }
}
#endif

void SaveManager::LoadSaveState(SaveState& SaveStateData)
{

// refactored approach using stringstream
#ifdef __EMSCRIPTEN__

  EM_ASM(
      {
        const SaveStateDataPtr = $0;
        const CallbackFunctionName = 'C_SaveManager_OnSyncfsLoadComplete';

        FS.syncfs(
            false, function(err) {
              if (err)
              {
	        console.error("Error syncing from IndexedDB (load):", err);
	        Module.ccall(CallbackFunctionName, null, [ 'number', 'number' ],
	                     [ SaveStateDataPtr, 0 ]);
              }
              else
              {
	        console.log("Synced from IndexedDB successfully for loading.");
	        Module.ccall(CallbackFunctionName, null, [ 'number', 'number' ],
	                     [ SaveStateDataPtr, 1 ]);
              }
            });
      },
      &SaveStateData, "C_SaveManager_OnSyncfsLoadComplete");

#else
  std::ifstream InputStream(SAVE_FILE_NAME, std::ios::binary);

  if (!InputStream.is_open())
    return;

  cereal::PortableBinaryInputArchive InputArchive(InputStream);
  InputArchive(SaveStateData);
#endif
}

void SaveManager::SaveStateData(SaveState& SaveStateData)
{

#ifdef __EMSCRIPTEN__
  std::ofstream OutputFileStream(EMSCRIPTEN_SAVE_FILE_NAME, std::ios::binary);
  if (!OutputFileStream.is_open())
  {
    std::cout << "unable to open the file via emscripten!";
    return;
  }

  // Scope to ensure Cereal flushes
  {
    cereal::PortableBinaryOutputArchive OutputArchive(OutputFileStream);
    OutputArchive(SaveStateData);
  }

  OutputFileStream.close();
  EM_ASM(FS.syncfs(
      false, function(err) {
        if (err)
        {
          console.error("Error syncing to IndexedDB (save):", err);
        }
        else
        {
          console.log("Saved to IndexedDB successfully via C++ interop");
        }
      }));
#else
  std::ofstream OutputFileStream(SAVE_FILE_NAME, std::ios::binary);
  if (!OutputFileStream.is_open())
    return;

  cereal::PortableBinaryOutputArchive OutputArchive(OutputFileStream);
  OutputArchive(SaveStateData);

#endif
}
