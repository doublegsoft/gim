/*
 *             o8o                    
 *             `"'                    
 *  .oooooooo oooo  ooo. .oo.  .oo.   
 * 888' `88b  `888  `888P"Y88bP"Y88b  
 * 888   888   888   888   888   888  
 * `88bod8P'   888   888   888   888  
 * `8oooooo.  o888o o888o o888o o888o 
 * d"     YD                          
 * "Y88888P'                          
 */

if (typeof gim == 'undefined') 
  gim = {};

gim.OP_ERROR = 'error';
gim.OP_LOGIN = 'login';
gim.OP_LOGOUT = 'logout';
gim.OP_CREATE_CONVERSATION = 'createConversation';
gim.OP_GET_CONVERSATIONS = 'getConversations';
gim.OP_ADD_CONVERSATION_MEMBER = 'addConversationMember';
gim.OP_SEND_MESSAGE = 'sendMessage';
gim.OP_GET_MESSAGES = 'getMessages';

gim.init = () => {
  gim.ws = new WebSocket('wss://gim.cq-fyy.com');
  gim.handlers = {};
  gim.ws.onmessge = (event) => {
    let data = event.data;
    let op = data.op;
    if (op == gim.OP_LOGIN) {
      gim.handlers[op](data.data, data.error);
    }
    if (op == gim.OP_LOGOUT) {
      gim.handlers[op](data.data, data.error);
    }
    if (op == gim.OP_CREATE_CONVERSATION) {
      gim.handlers[op](data.data, data.error);
    }
    if (op == gim.OP_GET_CONVERSATIONS) {
      gim.handlers[op](data.data, data.error);
    }
    if (op == gim.OP_ADD_CONVERSATION_MEMBER) {
      gim.handlers[op](data.data, data.error);
    }
    if (op == gim.OP_SEND_MESSAGE) {
      gim.handlers[op](data.data, data.error);
    }
    if (op == gim.OP_GET_MESSAGES) {
      gim.handlers[op](data.data, data.error);
    }
  };
};

gim.login = async (params) => {
  let req = {
    operation: 'login',
    payload: {
      memberId: params.memberId,
      memberType: params.memberType,
    }
  };
  gim.send(JSON.stringify(req));
};

gim.logout = async (params) => {
  let req = {
    operation: 'logout',
    payload: {
      sessionId: params.sessionId,
    }
  };
  gim.send(JSON.stringify(req));
};

gim.createConversation = async (params) => {
  let req = {
    operation: 'createConversation',
    payload: {
      memberId: params.memberId,
      memberType: params.memberType,
    }
  };
  gim.send(JSON.stringify(req));
};

gim.getConversations = async (params) => {
  let req = {
    operation: 'getConversations',
    payload: {
      memberId: params.memberId,
      memberType: params.memberType,
    }
  };
  gim.send(JSON.stringify(req));
};

gim.addConversationMember = async (params) => {
  let req = {
    operation: 'addConversationMember',
    payload: {
      conversationId: params.conversationId,
      memberId: params.memberId,
      memberType: params.memberType,
    }
  };
  gim.send(JSON.stringify(req));
};

gim.sendMessage = async (params) => {
  let req = {
    operation: 'sendMessage',
    payload: {
      conversationId: params.conversationId,
      senderId: params.senderId,
      senderType: params.senderType,
      messageType: params.messageType,
      messageContent: params.messageContent,
    }
  };
  gim.send(JSON.stringify(req));
};

gim.getMessages = async (params) => {
  let req = {
    operation: 'getMessages',
    payload: {
      conversationId: params.conversationId,
      memberId: params.memberId,
      memberType: params.memberType,
      lastConversationTime: params.lastConversationTime,
    }
  };
  gim.send(JSON.stringify(req));
};
