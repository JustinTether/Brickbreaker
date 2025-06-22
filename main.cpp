#include "engine/GameState.h"
#include "main.h"
int main()
{

#ifdef __EMSCRIPTEN__
  // Mount IDBFS at /save_data directory in the virtual file system
  // This needs to be done once, typically at the start of your application.
  // The directory "/save_data" will be backed by IndexedDB.
  // The filename SAVE_FILENAME ("savegame.dat") will then be relative to the
  // root, so if you want it inside this persistent mount, use
  // "/save_data/savegame.dat". For this example, we'll assume SAVE_FILENAME is
  // at the root, which can also be persisted. The root directory (/) can also
  // be an IDBFS mount.
  EM_ASM(FS.mkdir('/save_data'); // Create a directory if it doesn't exist
         FS.mount(IDBFS, {autoPersist : true},
                  '/save_data'); // Mount IDBFS to that directory

         // IMPORTANT : Initial sync to load any existing data from IndexedDB
         // into the virtual FS This is an asynchronous operation.
         FS.syncfs(
             true, function(err) {
               if (err)
               {
                 console.error("Initial syncfs error:", err);
               }
               else
               {
                 console.log(
                     "Initial syncfs complete. Persistent storage is ready.");
               }
             }););
#endif
  Engine* demo = Engine::Get();
  if (demo->Construct(demo->GameState->MapWidth * demo->TileSize.x,
                      demo->GameState->MapHeight * demo->TileSize.y, 2, 2))
    demo->Start();
  return 0;
}
