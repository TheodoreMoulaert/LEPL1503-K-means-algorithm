import matplotlib.pyplot as plt
import numpy as np

# Données des temps d'exécution
n_threads = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
temps_1 = [0.2, 0.166, 0.132, 0.138, 0.155, 1.295, 0.761, 0.565, 0.683, 0.732]  
temps_2 = [0.228, 0.16, 0.144, 0.161, 0.169, 1.301, 0.756, 0.547, 0.688, 0.629]  
temps_3 = [0.167, 0.144, 0.136, 0.173, 0.116, 1.296, 0.753, 0.574, 0.674, 0.688]

# Calcul des temps min et max
temps_min = [min(t1, t2, t3) for t1, t2, t3 in zip(temps_1, temps_2, temps_3)]
temps_max = [max(t1, t2, t3) for t1, t2, t3 in zip(temps_1, temps_2, temps_3)]

# Calcul du temps moyen
temps_moy = [(t1 + t2 + t3) / 3 for t1, t2, t3 in zip(temps_1, temps_2, temps_3)]

# Création du graphique
plt.figure(figsize=(10, 6))

# Tracé des lignes verticales entre temps min et temps max
for i, thread in enumerate(n_threads):
    plt.plot([thread, thread], [temps_min[i], temps_max[i]], color='blue', linewidth=2)
    plt.scatter(thread, temps_min[i], marker='o', color='green', label='Temps min' if i == 0 else "")
    plt.scatter(thread, temps_max[i], marker='o', color='red', label='Temps max' if i == 0 else "")
    plt.plot(thread, temps_moy[i], marker='o', markersize=5, color='orange', linestyle='dotted')  # Relier les points moyens en pointillé

# Relier les points moyens jaunes entre eux
plt.plot(n_threads, temps_moy, color='orange', linestyle='dotted')

# Affichage des annotations
for i, txt in enumerate(n_threads):
    plt.annotate(f"Moyenne: {temps_moy[i]:.2f}", (n_threads[i], temps_moy[i]), textcoords="offset points", xytext=(0,10), ha='center', fontsize=8)

# Configuration du graphique
plt.title("Temps d'exécution en fonction du nombre de threads")
plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution [s]")
plt.xticks(n_threads)
plt.grid(True)
plt.legend()

# Affichage du graphique
plt.tight_layout()
plt.show()