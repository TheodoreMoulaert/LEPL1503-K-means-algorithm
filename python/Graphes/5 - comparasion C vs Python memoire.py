import matplotlib.pyplot as plt

# Tailles de fichiers
tailles_fichier = ["2 threads", "4 threads", "6 threads","8 threads","10 threads"]

# Données de consommation de mémoire pour Python (exemples)
memoire_C = [39966, 40510, 41054, 41598,42142 ]  # Exemple de liste de consommation de mémoire pour C

# Création du graphique
plt.figure(figsize=(10, 6))

# Tracé des lignes pour la consommation de mémoire de Python et de C
plt.plot(tailles_fichier, memoire_C, label='C', marker='o')

# Configuration du graphique
plt.title("Comparaison de la consommation en fonction du nombre de threads")
plt.xlabel("Taille du fichier")
plt.ylabel("Consommation de mémoire [bytes]")
plt.grid(True)
plt.legend()

# Affichage du graphique
plt.tight_layout()
plt.show()
