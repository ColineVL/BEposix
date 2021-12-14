import sys
import pandas as pd

version = "lf"
filename = f"./res_log_arthur_{version}.txt"

with open(filename) as f:
    lines = f.readlines()

f.close()

repeat_factor = 2

loss_rates = {} # for each number of clients get percentage of clients never served as a fraction
max_latencies = {} # for each number of clients get maximum service delay
mean_latencies = {} # for each number of clients get mean latency
mean_launch_times = {} # for each number of clients get mean launching time of the nunch of clients by bash
clients_per_sec = {} # for each number of clients get clients served per second

n_clients = -1
real_n_clients = 0
launch_times_sum = 0
iteration_count = 0
latencies_sum = 0
max_latency = 0
for line in lines:
    info = line.strip("\n").split(" - ")
    if "n_clients" in line:
        if n_clients>0:
            loss_rates[n_clients] = (n_clients - real_n_clients/repeat_factor)/n_clients
            max_latencies[n_clients] = max_latency
            mean_latencies[n_clients] = latencies_sum/real_n_clients ## by what to divide ?
            mean_launch_times[n_clients] = launch_times_sum/iteration_count
            clients_per_sec[n_clients] = (real_n_clients/repeat_factor)/max_latency
            real_n_clients = 0
            launch_times_sum = 0
            iteration_count = 0
            latencies_sum = 0
            max_latency = 0
        n_clients = int(info[1])
    elif "launch_time" in line:
        launch_times_sum += float(info[1])
        iteration_count += 1
    else:
        assert n_clients>0
        real_n_clients += 1
        latencies_sum += float(info[1])
        max_latency = max(max_latency, float(info[1]))
loss_rates[n_clients] = (n_clients - real_n_clients/repeat_factor)/n_clients
max_latencies[n_clients] = max_latency
mean_latencies[n_clients] = latencies_sum/real_n_clients ## by what to divide ?
mean_launch_times[n_clients] = launch_times_sum/iteration_count
clients_per_sec[n_clients] = real_n_clients/max_latency


data = pd.DataFrame({
    "loss_rate" : loss_rates,
    "max_latency" : max_latencies,
    "mean_latency" : mean_latencies,
    "mean_launch_time" : mean_launch_times,
    "clients_per_sec" : clients_per_sec,
})
data.index.rename("n_clients", inplace = True)

print(data)

data.to_csv(f"./metrics_arthur_{version}.csv")