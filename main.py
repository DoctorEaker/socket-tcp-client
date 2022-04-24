import sys
import socket
import select
from urllib.parse import urlparse

filename = sys.argv[1]
url = sys.argv[2]

parsedUrl = urlparse(url)
host = parsedUrl.hostname
path = parsedUrl.path
port =  '80' if (parsedUrl.port is None) else parsedUrl.port


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, 80))

s.sendall(str.encode('GET '+path+' HTTP/1.1\r\nHOST: '+host+'\r\n\r\n'))

reply = b''

while select.select([s], [], [], 3)[0]:
    data = s.recv(2048)
    if not data: break
    reply += data

headers =  reply.split(b'\r\n\r\n')[0]
image = reply[len(headers)+4:]

# save image
f = open('downloads/'+filename, 'wb')
f.write(image)
f.close()