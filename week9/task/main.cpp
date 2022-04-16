#include "Reader.h"
#include "Writer.h"
#include "InterruptableThread.h"

int main() {
//    boost::interprocess::shared_memory_object::remove("managed_shared_memory");
    InterruptableThread thread;
    Reader reader(std::this_thread::get_id());
    Writer writer;
    thread.start([&reader](const StopToken &token) {
        reader.run(token);
    });
    writer.run(thread.stopToken());
    if (thread.joinable()) {
        thread.join();
    }
    return 0;
}