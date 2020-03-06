from http.server import BaseHTTPRequestHandler, HTTPServer
import base64
from urllib.parse import urlparse
import ssl
import http.client

class ProxyServerHandler(BaseHTTPRequestHandler):
	
	def do_GET(self):
		
		# EXTERNAL SERVER CONFIGURATION
		
		SERVER = 'localhost'
		PORT = 8081
		METHOD = 'POST'
		
		# connect to HTTPS with SSL = true or HTTP with SSL = false
		SSL = True
		
		# credentials for basic authentication
		USERNAME = 'login'
		PASSWORD = 'password'
		
		# END of external server configuration
		
		# print debug info
		DEBUG = True
		
		
		params = urlparse(self.path).query
		if DEBUG:
			print("\n--------------- NEW REQUEST ----------------")
			print("GET")
			print(self.path)
			print(self.headers)
			print(params)
		key = base64.b64encode(bytes('%s:%s' % (USERNAME, PASSWORD), 'utf-8')).decode('ascii')
		headers = {
			"User-Agent": "webproxy v0.1",
			"Authorization": 'Basic ' + str(key),
			"Content-type": "application/x-www-form-urlencoded",
			"Content-length": len(params)
			}
		headers.update(self.headers)
		if SSL:
			ctx = ssl.SSLContext()
			ctx.verify_mode = ssl.CERT_NONE
			conn = http.client.HTTPSConnection(SERVER, PORT, context=ctx)
		else:
			conn = http.client.HTTPConnection(SERVER, PORT)
		conn.request(METHOD, "", params, headers)
		response = conn.getresponse()
		data = response.read()
		self.send_response(200)
		self.send_header('Content-type', response.getheader('Content-type','text/html'))
		self.send_header('Content-length', len(data))
		self.end_headers()
		self.wfile.write(data)
		if DEBUG:
			print(data.decode('utf-8'))
			print("---------------------------------------------\n\n")
		
if __name__ == '__main__':
	
	# PROXY SERVER CONFIGURATION
	
	PORT = 8080
	
	# END of proxy server configuration
	
	print("\nStarting proxy server. Listening port", PORT, "...\n")
	server = HTTPServer(('', PORT), ProxyServerHandler)
	try:
		server.serve_forever()
	except KeyboardInterrupt:
		pass
	server.server_close()
	print("\nStopping proxy server...\n")
