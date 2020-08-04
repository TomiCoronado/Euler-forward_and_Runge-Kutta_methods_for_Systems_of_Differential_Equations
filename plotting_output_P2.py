import pandas as pd
from matplotlib import pyplot as plt 

output_P2 = pd.read_csv("output_P2.csv")

fig, axs = plt.subplots(3, 2)

# Euler forward method:
axs[0, 0].plot(output_P2.w_expl_0,output_P2.w_expl_1)
axs[0, 0].plot(output_P2.exact_solution_0,output_P2.exact_solution_1)
axs[0, 0].set_title("Euler forward method")
axs[0, 0].set_xlabel("y1")
axs[0, 0].set_ylabel("y2")
axs[0, 0].legend(["Euler forward","Exact solution"])

axs[1, 0].plot(output_P2.time,output_P2.w_expl_0)
axs[1, 0].plot(output_P2.time,output_P2.exact_solution_0)
axs[1, 0].set_xlabel("t")
axs[1, 0].set_ylabel("y1")
axs[1, 0].legend(["Euler forward","Exact solution"])
axs[1, 0].sharey(axs[0, 0])

axs[2, 0].plot(output_P2.time,output_P2.w_expl_1)
axs[2, 0].plot(output_P2.time,output_P2.exact_solution_1)
axs[2, 0].set_xlabel("t")
axs[2, 0].set_ylabel("y2")
axs[2, 0].legend(["Euler forward","Exact solution"])
axs[2, 0].sharey(axs[0, 0])

# Runge-Kutta with two stages (RK2) method:
axs[0, 1].plot(output_P2.w_RK2_0,output_P2.w_RK2_1)
axs[0, 1].plot(output_P2.exact_solution_0,output_P2.exact_solution_1)
axs[0, 1].set_title("Runge-Kutta with two stages (RK2) method")
axs[0, 1].set_xlabel("y1")
axs[0, 1].set_ylabel("y2")
axs[0, 1].legend(["Runge-Kutta","Exact solution"])
axs[0, 1].sharey(axs[0, 0])

axs[1, 1].plot(output_P2.time,output_P2.w_RK2_0)
axs[1, 1].plot(output_P2.time,output_P2.exact_solution_0)
axs[1, 1].set_xlabel("t")
axs[1, 1].set_ylabel("y1")
axs[1, 1].legend(["Runge-Kutta","Exact solution"])
axs[1, 1].sharey(axs[0, 0])

axs[2, 1].plot(output_P2.time,output_P2.w_RK2_1)
axs[2, 1].plot(output_P2.time,output_P2.exact_solution_1)
axs[2, 1].set_xlabel("t")
axs[2, 1].set_ylabel("y2")
axs[2, 1].legend(["Runge-Kutta","Exact solution"])
axs[2, 1].sharey(axs[0, 0])

fig.tight_layout()
plt.show()



