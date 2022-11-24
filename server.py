from http.server import BaseHTTPRequestHandler, HTTPServer
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore
import time
from datetime import datetime
import random

cred = credentials.Certificate('serviceAccount.json')

app = firebase_admin.initialize_app(cred)

db = firestore.client()
def guardaDato(char):
    while True:
        print("Sending data")
        current_date = datetime.now()
        date = current_date.strftime('%Y-%m-%d')
        hour = current_date.strftime('%H')
        collectionName = u'sensor_daniel_{0}'.format(date)
        encendido = bool(random.getrandbits(1))
        hour_ref = db.collection(collectionName).document(hour)
        totals_ref = db.collection(collectionName).document('totals')
        totals_doc = totals_ref.get()
        totals_data = totals_doc.to_dict()
        if totals_data == None:
            totals_ref.set({
                u'total_minutos_encendido': 1 if encendido else 0,
            })
        else:
            if encendido:
                totals_ref.update({
                    u'total_minutos_encendido': totals_data[u'total_minutos_encendido'] + 1
                })
     
       

        time.sleep(10)
    

class MyServer(BaseHTTPRequestHandler):
    def _set_response(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
    
    def do_GET(self):
        print("Hola desde el GET")
        if "/sensor1_temp" in self.path:
            sensor1_temp = self.path.split("=")[1]
            print("La temperatura es {}".format(sensor1_temp))        
        self._set_response()
        self.wfile.write("Hola este mi super server. GET requeste for {}".format(self.path).encode('utf-8'))


port = 8080
server_address = ('', port)
httpd = HTTPServer(server_address, MyServer)
httpd.serve_forever()