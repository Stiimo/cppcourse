#include "ShmClient.h"

class Writer : public ShmClient {
public:
    void run(const StopToken &stopToken) final;
};
