#include <iostream>
#include <string>

#include <grpcpp/grpcpp.h>
#include "notify.grpc.pb.h"
#include "Client.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;


NotifyClient::NotifyClient(std::shared_ptr<Channel> channel)
    : stub_(Notify::NewStub(channel)) {}


void NotifyClient::Subscribe() {

    SubscribeRequest request;
    ClientContext context;
    auto reader = stub_->Subscribe(&context, request);

    SubscribeResponse reply;
    while (reader->Read(&reply)) {

        std::string msg;
        switch (reply.notification_case())
        {
        case SubscribeResponse::NotificationCase::kAlert :
            msg = "alert received";
        case SubscribeResponse::NotificationCase::kError :
            msg = "error received";
        case SubscribeResponse::NotificationCase::kMessage :
            msg = "message received";
        case SubscribeResponse::NotificationCase::kWarning :
            msg = "warning received";
        case SubscribeResponse::NotificationCase::NOTIFICATION_NOT_SET :
            msg = "something went horrible wrong received";
        }
        std::cout << msg  << std::endl;
    }
}


int main() {
  NotifyClient client(grpc::CreateChannel(
      "50000", grpc::InsecureChannelCredentials()));

  client.Subscribe();
  return 0;
}
