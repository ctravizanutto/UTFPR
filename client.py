import socket
import pickle
from misc import server_address

if __name__ == "__main__":

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        try:
            client_socket.connect(server_address)
            print(f"[INFO] Connected to {server_address[0]}:{server_address[1]}")

            print('Numero de redes e a quantidade de máquinas de cada rede: ')
            buf = input()
            client_socket.sendall(buf.encode())

            response = pickle.loads(client_socket.recv(1024))
            for net_size, ip in response:
                print(f"{net_size}:", ip)
        except Exception as e:
            print(f"[ERROR] {e}")

        finally:
            client_socket.close()
