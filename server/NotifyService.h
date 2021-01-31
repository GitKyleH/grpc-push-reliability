#ifndef NOTIFYSERVICE_H
#define NOTIFYSERVICE_H

#include <string>

#include "notify.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Logic and data behind the server's behavior.
class NotifyService final : public Notify::Service {
public:
    NotifyService() {}
    ~NotifyService() {}
private:
    Status Subscribe(ServerContext* context, const SubscribeRequest* request, grpc::ServerWriter<SubscribeResponse>* response) override;
};


#endif //NOTIFYSERVICE_H