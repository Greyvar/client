import socket
import threading
import logging
import player
import clgame
import tile
import random
import select
import time

class server_interface:
	sock = None
	thread = None

	def __init__(self, frame, renderer, clgame):
		self.frame = frame
		self.renderer = renderer
		self.connected = False
		self.clgame = clgame

	def connect(self):
		try:
			self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
			self.sock.connect(("localhost", 1337));
			self.sock.setblocking(True);
			self.thread = threading.Thread(target=self.read)

			logging.debug("Started server listener");
			self.renderer.serverHostname = "CONNECTED"
#			self.renderer.serverHostname = str(self.sock.getpeername())[0]

			self.thread.start();

			self.connected = True
		except:
			self.renderer.serverHostname = "N"
			self.connected = False

	def consumeNumber(self, line):
		line, val = self.consumeString(line);
 
		return [line, float(val)]

	def consumeBoolean(self, line):
		line, val = self.consumeString(line);
 
 		print val
		return [line, val == "True"]


	def consumeString(self, line):
		if line.find(",") == -1:
			return ["", line]

		val, remainder = line.split(",", 1)
		
		return [remainder, val]

	def read(self):
		buf = ""

		while self.frame.running:
				char = self.sock.recv(1)
				if not char: break
				char = char.decode("utf-8")

				if char == "\n":
					self.read_line(buf);
					buf = "";
				else:
					buf += char;
		 
		logging.debug("Server reading thread is finished.");

	def read_line(self, line):
		#logging.debug("rcvd from server: " + line);
		cmd = line[0:4]

		if cmd == "SPWN":
			pass
#			self.renderer.playerMove();
		elif cmd == "PLRJ":
			self.read_player_join(line);
		elif cmd == "MOVE":
			self.read_move(line)
		elif cmd == "TILE":
			self.read_tile(line)
		elif cmd == "PLRU":
			self.read_player_you(line)
		elif cmd == "MESG":
			self.read_mesg(line);
		else: 
			logging.debug("Unhandled command from server: " + line)
			
	def read_mesg(self, line):
		line = line[5:999]
		line, message = self.consumeString(line);
		 
		self.renderer.addMessage(message);

	def read_player_you(self, line):
		self.localPlayer = player.player(None, None)

		line = line[5:999]
		line, self.localPlayer.id = self.consumeNumber(line);
		line, self.localPlayer.nickname = self.consumeString(line); 
		line, self.localPlayer.tex = self.consumeString(line);

	def read_tile(self, line):
		line = line[5:999]
		print line
		line, row = self.consumeNumber(line)
		line, col = self.consumeNumber(line)
		line, tex = self.consumeString(line)
		line, rot = self.consumeNumber(line)
		line, flipV = self.consumeBoolean(line)
		line, flipH = self.consumeBoolean(line)

		self.clgame.m.setTile(row, col, tile.tile(tex, False, rot, flipV, flipH))

	def read_move(self, line):
		line = line[5:999]
		line, playerId = self.consumeNumber(line)
		line, posX = self.consumeNumber(line);
		line, posY = self.consumeNumber(line);

		plr = self.clgame.getPlayer(playerId);
		plr.lastX = plr.x
		plr.lastY = plr.y
		plr.lastMoved = time.time()
		plr.x = posX;
		plr.y = posY;
		   
		logging.debug("pos: " + str(posX) + ":" + str(posY))

		self.renderer.draw()

	def read_player_join(self, line):
		line = line[5:999]
		line, id = self.consumeNumber(line)
		line, nickname = self.consumeString(line)
		line, skin = self.consumeString(line)

		if self.localPlayer.id == id:
			p = self.localPlayer
		else:
			p = player.player(id, nickname)
			p.tex = skin

		logging.debug("client doing player join: "  + ":" + str(id) + ":" + str(nickname))

		self.renderer.addPlayer(p)
		self.clgame.addPlayer(p, id)
		logging.debug(self.clgame.players)

	def send_helo(self):
		self.send("HELO " + random.choice(["Alice", "Bob", "Charles", "Dave"]));

	def disconnect(self):
		if self.sock != None:
			self.send("BYEE")
			self.sock.shutdown(socket.SHUT_RDWR)
			self.sock.close();

	def send_halt(self):
		self.send("HALT");

	def send(self, message):
		if not self.connected: 
			logging.warning("Cannot move player. Not connected to server.")
			return
 
		self.sock.send(message.encode("utf-8"));

	def send_move(self, x, y):
		self.send("MOVR " + str(int(self.localPlayer.id)) + "," + str(int(x)) + "," + str(int(y)) + "\n");
