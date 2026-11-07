#include <mutex>

void Update(std::mutex& m, Database& db)
{
    const std::lock_guard<std::mutex> lock(m);
    if (!db.isReady()) return; // if isReady returns, m.unlock() is never called, so mutex stays locked
    db.write(getData()); // same here if it throws an error, m.unlock() is never called
}