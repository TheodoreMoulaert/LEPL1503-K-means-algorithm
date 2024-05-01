import matplotlib.pyplot as plt

# Tailles de fichiers
tailles_fichier = ["7 points", "50 points", "100 points"]

# Données de consommation de mémoire pour Python (exemples)
memoire_python = [100, 200, 300]  # Exemple de liste de consommation de mémoire pour Python
memoire_C = [50, 150, 250]  # Exemple de liste de consommation de mémoire pour C

# Création du graphique
plt.figure(figsize=(10, 6))

# Tracé des lignes pour la consommation de mémoire de Python et de C
plt.plot(tailles_fichier, memoire_python, label='Python', marker='o')
plt.plot(tailles_fichier, memoire_C, label='C', marker='o')

# Configuration du graphique
plt.title("Comparaison de la consommation de mémoire entre C et Python")
plt.xlabel("Taille du fichier")
plt.ylabel("Consommation de mémoire [Mo]")
plt.grid(True)
plt.legend()

# Affichage du graphique
plt.tight_layout()
plt.show()
