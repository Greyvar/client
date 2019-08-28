#pragma once

#include <grpc++/grpc++.h>

#include <boleas/gui/Gui.hpp>

#include "server_interface.grpc.pb.h"

#include <queue>

using greyvarproto::ServerInterface;
using greyvarproto::ConnectionRequest;
using greyvarproto::ConnectionResponse;
using greyvarproto::ClientRequests;
using greyvarproto::ServerFrameResponse;
using grpc::Channel;
using grpc::ClientContext;

using std::queue;

using std::cout;
using std::endl;

class NetClient {
	public:
		NetClient(NetClient const&) = delete;
		void operator=(NetClient const&) = delete;

		static NetClient& get() {
			static NetClient instance(grpc::CreateChannel("localhost:2000", grpc::InsecureChannelCredentials()));

			return instance;
		}

		ClientRequests* nextFrameToSend = new ClientRequests(); 
		queue<ServerFrameResponse> serverFrameBuffer;

		void connect() {
			ConnectionRequest req; 
			ConnectionResponse res;
			ClientContext ctx;

			stub_->Connect(&ctx, req, &res);

			Gui::get().scene = PLAY;
			Gui::get().addMessage("connected to server");

			cout << "server version" << res.serverversion() << endl;
		}

		ClientRequests* getNextFrameToSend() {
			return this->nextFrameToSend;
		}

		bool hasFrames() {
			return !this->serverFrameBuffer.empty();
		}

		void processServerFrames() {
			while (this->hasFrames()) {
				auto frame = this->serverFrameBuffer.front();

				cout << "Processing server frame" << endl;
			}
		}

		void sendRecvFrame() {
			ServerFrameResponse res;
			ClientContext ctx;

			auto s = stub_->GetServerFrame(&ctx, *this->nextFrameToSend, &res);

			this->nextFrameToSend = new ClientRequests();

			if (!s.ok()) {
				cout << "omg, srv frame fail: " << s.error_message() << endl;
			} else {
				serverFrameBuffer.push(res);
			}
		}

	private:
		NetClient(std::shared_ptr<Channel> channel) : stub_(ServerInterface::NewStub(channel)) {
			cout << "NetClient" << endl;
		}
		
		std::unique_ptr<ServerInterface::Stub> stub_;
};
