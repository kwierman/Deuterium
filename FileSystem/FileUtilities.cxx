#include "Deuterium/FileSystem/FileUtilities.h"


static inline unsigned Deuterium::FileSystem::SwapWord(const unsigned& word){
    return (
        ((word & 0xff000000) >> 24) |
        ((word & 0x00ff0000) >> 8) |
        ((word & 0x0000ff00) << 8) |
        ((word & 0x000000ff) << 24)
    );
}