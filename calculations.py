import ipaddress

def calculate_subnet_range(hosts_count, ip):
    mask = 32 - (host_bits := hosts_count.bit_length())

    base_network = ipaddress.IPv4Network(ip, strict=False)
    subnet_network = ipaddress.IPv4Network(f"{base_network.network_address}/{mask}", strict=False)

    first_ip = str(subnet_network.network_address)
    last_ip = str(subnet_network.broadcast_address)

    return first_ip, last_ip, mask

def get_next_network_ip(ip, subnet_mask):
    network = ipaddress.IPv4Network(f'{ip}/{subnet_mask}', strict=False)
    next_network_ip = network.network_address + network.num_addresses

    return str(next_network_ip)

def networks(network_sizes):
    network_sizes.sort(reverse=True)
    first_ip = "192.168.0.0"
    ip_list = []
    for network in network_sizes:
        first_ip, last_ip, mask = calculate_subnet_range(network, first_ip)
        ip_list.append(first_ip + '/' + mask)

        #print(f"First IP address for {first_ip}/{mask}")
        first_ip = get_next_network_ip(last_ip, mask)

    return ip_list
