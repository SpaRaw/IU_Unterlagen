import psutil

def find_node_processes():
    node_processes = []
    for proc in psutil.process_iter(['pid', 'name', 'cmdline']):
        if proc.info['name'] == 'node':
            node_processes.append(proc.info)
    return node_processes

if __name__ == "__main__":
    node_processes = find_node_processes()
    if node_processes:
        for process in node_processes:
            print(f"PID: {process['pid']}, Command Line: {' '.join(process['cmdline'])}")
    else:
        print("No Node.js processes found.")