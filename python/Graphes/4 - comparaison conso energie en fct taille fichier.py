import matplotlib.pyplot as plt
import numpy as np

# Données de la consommation d'énergie
n_threads = list(range(1, 11))
energie_1 = [0.000119634,0.000143364,9.88958*10**(-5),8.28761*10**(-5),8.47652*10**(-5),8.56396*10**(-5),9.49026*10**(-5),9.55058*10**(-5),9.05259*10**(-5),9.85498*10**(-5)]  # Exemple de liste de consommation d'énergie en Wh

# Conversion de Wh en kWh pour la moyenne
energie_kwh = [e / 1000 for e in energie_1]

# Calcul de la consommation d'énergie moyenne en kWh
energie_moy = np.mean(energie_kwh)

# Création du graphique
plt.figure(figsize=(10, 6))

# Tracé des points de consommation d'énergie
plt.plot(n_threads, energie_kwh, color='blue', marker='o', label='Consommation d\'énergie')

# Tracé de la ligne pour la consommation d'énergie moyenne
plt.plot(n_threads, [energie_moy] * len(n_threads), color='orange', linestyle='dotted', label='Consommation moyenne')

# Affichage des annotations
for i, txt in enumerate(n_threads):
    plt.annotate(f"Consommation: {energie_1[i]} Wh", (n_threads[i], energie_kwh[i]), textcoords="offset points", xytext=(0,10), ha='center')

plt.annotate(f"Moyenne: {energie_moy:.2f} kWh", (n_threads[-1], energie_moy), textcoords="offset points", xytext=(0,10), ha='center')

# Configuration du graphique
plt.title("Consommation d'énergie en fonction du nombre de threads")
plt.xlabel("Nombre de threads")
plt.ylabel("Consommation d'énergie [kWh]")
plt.xticks(n_threads)
plt.grid(True)
plt.legend()

# Affichage du graphique
plt.tight_layout()
plt.show()

