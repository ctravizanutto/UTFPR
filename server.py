import socket
from calculations import networks

if __name__ == "__main__":
    server_address = ('localhost', 8080)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind(server_address)
        server_socket.listen(1)
        print(f"[INFO] Listening on {server_address[0]}:{server_address[1]}")
        

        while True:
            client_socket, client_address = server_socket.accept()
            print(f"[INFO] Accepted connection from {client_address[0]}:{client_address[1]}")

            try:
                data = client_socket.recv(1024)

                response = networks(data)
                client_socket.sendall(response.encode())
            except Exception as e:
                print(f"[ERROR] {e}")
            finally:
                client_socket.close()
                print("[INFO] Connection closed\n")

