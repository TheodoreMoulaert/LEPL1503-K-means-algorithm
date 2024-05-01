import matplotlib.pyplot as plt
import numpy as np

# Données de la consommation mémoire
n_threads = [1, 2, 3, 4, 5, 6, 7]
memoire_1 = [100, 150, 200, 250, 300, 350, 400]  # Exemple de liste de consommation mémoire
memoire_2 = [110, 160, 210, 260, 310, 360, 410]  # Exemple de liste de consommation mémoire
memoire_3 = [120, 170, 220, 270, 320, 370, 420]  # Exemple de liste de consommation mémoire

# Calcul de la consommation mémoire min et max
memoire_min = [min(m1, m2, m3) for m1, m2, m3 in zip(memoire_1, memoire_2, memoire_3)]
memoire_max = [max(m1, m2, m3) for m1, m2, m3 in zip(memoire_1, memoire_2, memoire_3)]

# Calcul de la consommation mémoire moyenne
memoire_moy = [(m1 + m2 + m3) / 3 for m1, m2, m3 in zip(memoire_1, memoire_2, memoire_3)]

# Création du graphique
plt.figure(figsize=(10, 6))

# Tracé des lignes verticales entre consommation mémoire min et max
for i, thread in enumerate(n_threads):
    plt.plot([thread, thread], [memoire_min[i], memoire_max[i]], color='blue', linewidth=2)
    plt.scatter(thread, memoire_min[i], marker='o', color='green', label='Memoire min' if i == 0 else "")
    plt.scatter(thread, memoire_max[i], marker='o', color='red', label='Memoire max' if i == 0 else "")
    plt.plot(thread, memoire_moy[i], marker='o', markersize=5, color='orange', linestyle='dotted')  # Relier les points moyens en pointillé

# Relier les points moyens jaunes entre eux
plt.plot(n_threads, memoire_moy, color='orange', linestyle='dotted')

# Affichage des annotations
for i, txt in enumerate(n_threads):
    plt.annotate(f"Moyenne: {memoire_moy[i]} Mo", (n_threads[i], memoire_moy[i]), textcoords="offset points", xytext=(0,10), ha='center')

# Configuration du graphique
plt.title("Consommation mémoire en fonction du nombre de threads")
plt.xlabel("Nombre de threads")
plt.ylabel("Consommation mémoire [Mo]")
plt.xticks(n_threads)
plt.grid(True)
plt.legend()

# Affichage du graphique
plt.tight_layout()
plt.show()
