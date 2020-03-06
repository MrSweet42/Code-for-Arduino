from http.server import BaseHTTPRequestHandler, HTTPServer
import base64
import json
from urllib.parse import urlparse, parse_qs
import cgi
from urllib import parse
import ssl

class CustomServerHandler(BaseHTTPRequestHandler):
	
	def do_HEAD(self):
		print("\n---------------- NEW REQUEST ----------------")
		print("HEAD")
		print(self.path)
		print(self.headers)
		self.send_response(200)
		self.send_header('Content-type', 'application/json')
		self.end_headers()
		print("---------------------------------------------\n\n")
	
	def do_AUTHHEAD(self):
		print("\n--------------- NEW REQUEST ----------------")
		print("AUTHHEAD")
		print(self.path)
		print(self.headers)
		self.send_response(401)
		self.send_header('WWW-Authenticate', 'Basic realm=\"Login\"')
		self.send_header('Content-type', 'application/json')
		self.end_headers()
		print("---------------------------------------------\n\n")
	
	def do_GET(self):
		print("\n--------------- NEW REQUEST ----------------")
		print("GET")
		print(self.path)
		print(self.headers)
		self.send_response(405)
		self.send_header('Content-type', 'application/json')
		self.end_headers()
		print("Method Not Allowed")
		get_params = parse_qs(urlparse(self.path).query)
		response = {
			'error': 'Method Not Allowed',
			'get_params': str(get_params)
		}
		print(get_params)
		self.wfile.write(bytes(json.dumps(response), 'utf-8'))
		print("---------------------------------------------\n\n")
		
	def do_POST(self):
		print("\n--------------- NEW REQUEST ----------------")
		print("POST")
		print(self.path)
		print(self.headers)
		key = self.server.get_auth_key()
		if self.headers.get('Authorization') == 'Basic ' + str(key):
			print("Successfully authenticated")
			get_params = parse_qs(urlparse(self.path).query)
			post_params = {}
			ctype, pdict = cgi.parse_header(self.headers.get('content-type'))
			if ctype == 'multipart/form-data':
				post_params = cgi.parse_multipart(self.rfile, pdict)
			elif ctype == 'application/x-www-form-urlencoded':
				length = int(self.headers.get('content-length'))
				post_params = parse.parse_qs(self.rfile.read(length).decode('utf-8'), keep_blank_values=1)
			response = {
				'get_params': get_params,
				'post_params': post_params
			}
			print(get_params)
			print(post_params)
			out = bytes(json.dumps(response), 'utf-8')
			self.send_response(200)
			self.send_header('Content-type', 'application/json')
			self.send_header('Content-length', len(out))
			self.end_headers()
			self.wfile.write(out)
		else:
			print("Authentication failed")
			self.do_AUTHHEAD()
			response = {
				'error': 'Authentication failed'
			}
			self.wfile.write(bytes(json.dumps(response), 'utf-8'))
		print("---------------------------------------------\n\n")

class CustomHTTPServer(HTTPServer):
	
	key = ''
	
	def __init__(self, address, handlerClass=CustomServerHandler):
		super().__init__(address, handlerClass)
	
	def set_auth(self, username, password):
		self.key = base64.b64encode(bytes('%s:%s' % (username, password), 'utf-8')).decode('ascii')
	
	def get_auth_key(self):
		return self.key

if __name__ == '__main__':
	
	# SERVER CONFIGURATION
	
	# run HTTPS with SSL = true or HTTP with SSL = false
	SSL = True
	
	PORT = 8081
	USERNAME = 'login'
	PASSWORD = 'password'
	
	# END of server configuration
	
	print("\nStarting", "secure HTTPS" if SSL else "non-secure HTTP", "web server. Listening port", PORT, "...\n")
	server = CustomHTTPServer(('', PORT))
	server.set_auth(USERNAME, PASSWORD)
	if SSL:
		server.socket = ssl.wrap_socket(server.socket, certfile='localhost.pem', server_side=True)
	try:
		server.serve_forever()
	except KeyboardInterrupt:
		pass
	server.server_close()
	print("\nStopping web server...\n")
