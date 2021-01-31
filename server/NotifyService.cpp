#include <string>

#include <grpcpp/grpcpp.h>

#include "NotifyService.h"

Status NotifyService::Subscribe(ServerContext* context, const SubscribeRequest* request, grpc::ServerWriter<SubscribeResponse>* response)
{
    std::string prefix("Hello ");
    SubscribeResponse reply;
    reply.mutable_alert()->set_message("generic alert");
    return Status::OK;
}