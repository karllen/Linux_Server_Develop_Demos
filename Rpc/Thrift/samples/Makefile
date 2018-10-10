C_DIR = .

ASYN_CLIENT_DIR = $(C_DIR)/Asynchronous/Client
ASYN_SERVER_DIR = $(C_DIR)/Asynchronous/Server
SYN_CLIENT_DIR = $(C_DIR)/Synchronous/Client
SYN_SERVER_DIR = $(C_DIR)/Synchronous/Server


all:targetAsynClient
targetAsynClient:targetAsynServer
	cd $(ASYN_CLIENT_DIR) && make
targetAsynServer:targetSyncClient
	cd $(ASYN_SERVER_DIR) && make
targetSyncClient:targetSyncServer
	cd $(SYN_CLIENT_DIR) && make
targetSyncServer:
	cd $(SYN_SERVER_DIR) && make



clean:cleanAsynClient
cleanAsynClient:cleanAsynServer
	cd $(ASYN_CLIENT_DIR) && make clean
cleanAsynServer:cleanSyncClient
	cd $(ASYN_SERVER_DIR) && make clean
cleanSyncClient:cleanSyncServer
	cd $(SYN_CLIENT_DIR) && make clean
cleanSyncServer:
	cd $(SYN_SERVER_DIR) && make clean
	

