C_DIR = .
SUB_HELLOWORD_DIR = $(C_DIR)/helloworld
SUB_PUBLISHSUBSCRIBE_DIR = $(C_DIR)/publishsubscribe
SUB_ROUTING_DIR = $(C_DIR)/routing
SUB_RPC_DIR = $(C_DIR)/rpc
SUB_TOPIC_DIR = $(C_DIR)/topics
SUB_WORKQUEUES_DIR = $(C_DIR)/workqueues


all:targethelloworld
targethelloworld:targetpublishsubscribe
	cd $(SUB_HELLOWORD_DIR) && make
targetpublishsubscribe:targetrouting
	cd $(SUB_PUBLISHSUBSCRIBE_DIR) && make
targetrouting:targetrpc
	cd $(SUB_ROUTING_DIR) && make
targetrpc:targettopics
	cd $(SUB_RPC_DIR) && make
targettopics:targetworkqueues
	cd $(SUB_TOPIC_DIR) && make
targetworkqueues:
	cd $(SUB_WORKQUEUES_DIR) && make

clean:cleanhelloworld
cleanhelloworld:cleanpublishsubscribe
	cd $(SUB_HELLOWORD_DIR) && make clean
cleanpublishsubscribe:cleanrouting
	cd $(SUB_PUBLISHSUBSCRIBE_DIR) && make clean
cleanrouting:cleanrpc
	cd $(SUB_ROUTING_DIR) && make clean
cleanrpc: cleantopics
	cd $(SUB_RPC_DIR) && make clean
cleantopics:cleanworkqueues
	cd $(SUB_TOPIC_DIR) && make clean
cleanworkqueues:
	cd $(SUB_WORKQUEUES_DIR) && make clean