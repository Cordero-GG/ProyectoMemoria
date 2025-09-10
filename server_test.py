import socket
import json
import threading

class TestServer:
    def __init__(self, host='127.0.0.1', port=8080):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.running = False

    def start(self):
        try:
            self.socket.bind((self.host, self.port))
            self.socket.listen(5)
            self.running = True
            print(f"Servidor de prueba escuchando en {self.host}:{self.port}")

            while self.running:
                client_socket, addr = self.socket.accept()
                print(f"Conexión establecida desde {addr}")
                client_thread = threading.Thread(target=self.handle_client, args=(client_socket,))
                client_thread.start()

        except Exception as e:
            print(f"Error en el servidor: {e}")
        finally:
            self.socket.close()

    def handle_client(self, client_socket):
        try:
            while True:
                data = client_socket.recv(4096)
                if not data:
                    break

                message = data.decode('utf-8')
                print("=" * 50)
                print("MENSAJE RECIBIDO:")

                # Intentar parsear como JSON
                try:
                    json_data = json.loads(message)
                    print(json.dumps(json_data, indent=2, ensure_ascii=False))
                except json.JSONDecodeError:
                    print("Mensaje no JSON:", message)

        except Exception as e:
            print(f"Error con cliente: {e}")
        finally:
            client_socket.close()

    def stop(self):
        self.running = False
        self.socket.close()

if __name__ == "__main__":
    server = TestServer()
    try:
        server.start()
    except KeyboardInterrupt:
        server.stop()
        print("Servidor detenido")