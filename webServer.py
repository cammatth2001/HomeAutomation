from flask_sockets import Sockets
import gevent
import time
import json


'''
Setting up the webserver
'''

app=Flask(__name__)
app.debug = True

'''
Secking up the websockets
'''

sockets = Sockets(app)

'''
handling multiple clients
'''

clients = list()

'''
User-defined class for clients
'''

class Client:
    def__init__(self):
        self.queue = gevent.queue.Queue()
    def put(self,v):
        self.queue.put_nowait(v)
    def get(self):
        return self.queue.get()

'''
adding a route to the websockets server
'''

@sockets.route('/echo')
def echo_sickets(ws)
    while not ws.closed:
        message = ws.recieve()
        ws.send(message) #simply send back the data

'''
adding a route to the websockets server to "subscribe" clients
'''

@sockets.route('/subscribe')
def subscribe_socket(ws):
    client = Client() #user-defined object to store client info
    clients.append(client)
    print '# Clients: {}'.format(len(clients))


