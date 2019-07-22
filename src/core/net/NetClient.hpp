#pragma once

#include <grpc++/grpc++.h>

#include <boleas/gui/Gui.hpp>

#include "server_interface.grpc.pb.h"

using greyvarproto::ServerInterface;
using greyvarproto::ConnectionRequest;
using greyvarproto::ConnectionResponse;
using grpc::Channel;
using grpc::ClientContext;

class NetClient {
	public:
		NetClient(NetClient const&) = delete;
		void operator=(NetClient const&) = delete;

		static NetClient& get() {
			static NetClient instance(grpc::CreateChannel("localhost:2000", grpc::InsecureChannelCredentials()));

			return instance;
		}

		void connect() {
			ConnectionRequest req; 
			ConnectionResponse res;
			ClientContext ctx;

			stub_->Connect(&ctx, req, &res);

			Gui::get().scene = PLAY;
			Gui::get().addMessage("connected to server");

			auto evt = new SDL_Event();

			SDL_PushEvent(&event);
		}

	private:
		NetClient(std::shared_ptr<Channel> channel) : stub_(ServerInterface::NewStub(channel)) {
			std::cout << "NetClient" << std::endl;
		}
		
		std::unique_ptr<ServerInterface::Stub> stub_;
};
